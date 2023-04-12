all:
	+$(MAKE) -C bootloader
	+$(MAKE) -C os

write:
	+$(MAKE) -C bootloader write

minicom:
	@echo "dip switch must be: ON OFF ON OFF"
	@sleep 1.5
	sudo minicom -D /dev/ttyUSB0 -b 9600 -8

clean:
	+$(MAKE) -C bootloader clean
	+$(MAKE) -C os clean
