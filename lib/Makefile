AS=arm-none-eabi-as
AR=arm-none-eabi-ar
CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
OBJCOPY=arm-none-eabi-objcopy
CPU=cortex-a8
CFLAGS=-g -I../include/ -Wall
ASFLAGS=-g
LDFLAGS=-T startup.ld
ARFLAGS=

all : libkyubey.a

libkyubey.a : kputs.o kprintf.o khexdump.o memcpy.o
	$(AR) rv $@ $^
%.o : %.s
	$(AS) -mcpu=$(CPU) $(ASFLAGS) $< -o $@
%.o : %.c
	$(CC) -c -mcpu=$(CPU) $(CFLAGS) $< -o $@

clean :
	rm -f *.o libkyubey.a
