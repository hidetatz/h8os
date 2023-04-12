#ifndef H8OS_BOOTLOADER_SERIAL_H_
#define H8OS_BOOTLOADER_SERIAL_H_

// initialize serial device
int serial_init(int index);

// check if send is enabled
int serial_is_send_enable(int index);

// send a byte
int serial_send_byte(int index, unsigned char b);

// check if receive is enabled
int serial_is_recv_enable(int index);

// receive a byte
unsigned char serial_recv_byte(int index);

#endif // H8OS_BOOTLOADER_SERIAL_H_
