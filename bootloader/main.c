/*
 * h8os bootloader.
 */

#include "util.h"
#include "serial.h"
#include "xmodem.h"
#include "interrupt.h"
#include "elf.h"
#include "lib.h"

static int init(void) {
	// defined in linker script
	extern int erodata, data_start, edata, bss_start, ebss;

	/*
	 * Initialize .data/.bss on *RAM* to allow writing variable.
	 */

	// copy .data from ROM to RAM. erodata is on ROM, data_start is on RAM.
	memcpy(&data_start, &erodata, (long)&edata - (long)&data_start);

	// write 0 on bss on RAM.
	memset(&bss_start, 0, (long)&ebss - (long)&bss_start);

	softvec_init();

	serial_init(SERIAL_DEFAULT_DEVICE);

	return 0;
}

static int dump(char *buf, long size) {
	long i;

	if (size < 0) {
		puts("no data\n");
		return -1;
	}

	for (i = 0; i < size; i++) {
		putxval(buf[i], 2);

		if ((i & 0xf) == 15) {
			puts("\n");
		} else {
			if ((i & 0xf) == 7) puts(" ");
			puts(" ");
		}
	}
	puts("\n");

	return 0;
}

static void wait() {
	volatile long i;
	for (i = 0; i < 300000; i++)
		;
}

int main(void) {
	static char buf[16];
	static long size = -1;
	static unsigned char *loadbuf = NULL;
	char *entrypoint;
	void (*f) (void);
	extern int buffer_start; // defined in linker script

	INTR_DISABLE;
	init();

	puts("h8os boot loader started.\n");
	
	while(1) {
		puts("bootloader> ");
		gets(buf);

		if (!strcmp(buf, "load")) {
			loadbuf = (char *)(&buffer_start);
			size = xmodem_recv(loadbuf);
			wait(); // wait for the xmodem file transfer app (minicom) termination to not lose the message
			if (size < 0) {
				puts("\nXMODEM receive error!\n");
			} else {
				puts("\nXMODEM receive succeeded.!\n");
			}
		} else if (!strcmp(buf, "dump")) {
			puts("size: ");
			putxval(size, 0);
			puts("\n");
			dump(loadbuf, size);
		} else if (!strcmp(buf, "run")) {
			entrypoint = elf_load(loadbuf);
			if (!entrypoint) {
				puts("run error!\n");
			} else {
				puts("starting from entrypoint: ");
				putxval((unsigned long)entrypoint, 0);
				puts("\n");
				f = (void (*)(void))entrypoint;
				f();
				// never gets back here
			}
		} else {
			puts("unknown.\n");
		}
	}

	return 0;
}
