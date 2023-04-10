#include "../util/defines.h"
#include "serial.h"
#include "lib.h"
#include "xmodem.h"

#define XMODEM_SOH 0x01
#define XMODEM_EOT 0x04
#define XMODEM_ACK 0x06
#define XMODEM_NAK 0x15
#define XMODEM_CAN 0x18

#define XMODEM_BLOCK_SIZE 128

static int xmodem_wait(void) {
	long cnt = 0;

	while (!serial_is_recv_enable(SERIAL_DEFAULT_DEVICE)) {
		if (++cnt >= 2000000) {
			cnt = 0;
			// In XMODEM, receiver keeps sending NAK to tell it's ready
			serial_send_byte(SERIAL_DEFAULT_DEVICE, XMODEM_NAK);
		}
	}

	return 0;
}

/*
 * Block format in XMODEM protocol:
 * 
 *┌───┬───┬───┬──────────────┬───┐
 *│ a │ b │ c │       d      │ e │
 *└───┴───┴───┴──────────────┴───┘
 * a(1-bit): SOH
 * b(1-bit): block number (1 -> 255, then gets back to -1)
 * c(1-bit): inverted block number (for check)
 * d(128-bit): actual data (eof-padding is applied)
 * e(1-bit): checksum
 */
static int xmodem_read_block(unsigned char block_number, char *buf) {
	unsigned char c, block_num, checksum;
	int i;

	// SOH is already read in xmodem_recv

	// read b(block_num)
	block_num = serial_recv_byte(SERIAL_DEFAULT_DEVICE);
	if (block_num != block_number)
		return -1;

	// read c. make sure c is inverted b
	block_num ^= serial_recv_byte(SERIAL_DEFAULT_DEVICE);
	if (block_num != 0xff)
		return -1;

	// read d
	checksum = 0;
	for (i = 0; i < XMODEM_BLOCK_SIZE; i++) {
		c = serial_recv_byte(SERIAL_DEFAULT_DEVICE);
		*(buf++) = c;
		checksum += c;
	}

	// read e and check checksum
	checksum ^= serial_recv_byte(SERIAL_DEFAULT_DEVICE);
	if (checksum)
		return -1;

	return i;
}

long xmodem_recv(char *buf) {
	int r, receiving = 0;
	long size = 0;
	unsigned char c, block_number = 1;

	while (1) {
		if (!receiving)
			xmodem_wait();

		c = serial_recv_byte(SERIAL_DEFAULT_DEVICE);

		if (c == XMODEM_EOT) {
			// Success path: send ACK and finish receiving.
			serial_send_byte(SERIAL_DEFAULT_DEVICE, XMODEM_ACK);
			break;
		} else if (c == XMODEM_CAN) {
			// Canceled from sender side.
			return -1;
		} else if (c == XMODEM_SOH) {
			// 132-bit block is coming.
			receiving++;
			r = xmodem_read_block(block_number, buf);
			if (r < 0) {
				// failed receiving the block; send NAK.
				serial_send_byte(SERIAL_DEFAULT_DEVICE, XMODEM_NAK);
			} else {
				block_number++;
				size += r;
				buf += r;
				serial_send_byte(SERIAL_DEFAULT_DEVICE, XMODEM_ACK);
			}
		} else {
			if (receiving)
				return -1;
		}
	}

	return size;
}
