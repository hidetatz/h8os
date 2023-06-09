PREFIX = /usr/local
ARCH = h8300-elf
BINDIR = $(PREFIX)/bin
ADDNAME = $(ARCH)-

AR      = $(BINDIR)/$(ADDNAME)ar
AS      = $(BINDIR)/$(ADDNAME)as
CC      = $(BINDIR)/$(ADDNAME)gcc
LD      = $(BINDIR)/$(ADDNAME)ld
NM      = $(BINDIR)/$(ADDNAME)nm
OBJCOPY = $(BINDIR)/$(ADDNAME)objcopy
OBJDUMP = $(BINDIR)/$(ADDNAME)objdump
RANLIB  = $(BINDIR)/$(ADDNAME)ranlib
STRIP   = $(BINDIR)/$(ADDNAME)strip

H8WRITE = ../romwriter/h8write

OBJS = vector.o startup.o main.o
OBJS += lib.o serial.o xmodem.o elf.o interrupt.o intr.o

H8RITE_SERDEV = /dev/ttyUSB0

TARGET = bl

CFLAGS = -Wall -mh -nostdinc -nostdlib -fno-builtin
CFLAGS += -I.
CFLAGS += -Os
CFLAGS += -DBOOTLOADER

LFLAGS = -static -T ld.scr -L.

.SUFFIXES: .c .o
.SUFFIXES: .s .o
.SUFFIXES: .S .o

all: $(TARGET)
	
$(TARGET): $(OBJS) ld.scr
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS) $(LFLAGS)
	cp $(TARGET) $(TARGET).elf
	$(STRIP) $(TARGET)

.c.o: $<
	$(CC) -c $(CFLAGS) $<

.s.o: $<
	$(CC) -c $(CFLAGS) $<

.S.o: $<
	$(CC) -c $(CFLAGS) $<

$(TARGET).mot: $(TARGET)
	$(OBJCOPY) -O srec $(TARGET) $(TARGET).mot

image: $(TARGET).mot

write: $(TARGET).mot
	@echo "dip switch must be: ON ON OFF ON"
	$(H8WRITE) -3069 -f20 $(TARGET).mot $(H8RITE_SERDEV)

minicom:
	@echo "dip switch must be: ON OFF ON OFF"
	@sleep 1.5
	sudo minicom -D /dev/ttyUSB0 -b 9600 -8

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).elf $(TARGET).mot
