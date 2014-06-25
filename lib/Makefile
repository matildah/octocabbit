AS=arm-none-eabi-as
AR=arm-none-eabi-ar
CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
OBJCOPY=arm-none-eabi-objcopy
CPU=arm926ej-s
CFLAGS=-g -I../include/
ASFLAGS=-g
LDFLAGS=-T startup.ld
ARFLAGS=

all : libkyubey.a

libkyubey.a : kputs.o
	$(AR) rvs $@ $^
%.o : %.s
	$(AS) -mcpu=$(CPU) $(ASFLAGS) $< -o $@
%.o : %.c
	$(CC) -c -mcpu=$(CPU) $(CFLAGS) $< -o $@

clean :
	rm -f *.o image.bin image.elf
