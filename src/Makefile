AS=arm-none-eabi-as
CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
OBJCOPY=arm-none-eabi-objcopy
CPU=arm926ej-s
CFLAGS=-g -I../include/ -Wall
ASFLAGS=-g
LDFLAGS=-T startup.ld -L../lib/
LIBRARIES=-lkyubey

%.o : %.s
	$(AS) -mcpu=$(CPU) $(ASFLAGS) $< -o $@
%.o : %.c
	$(CC) -c -mcpu=$(CPU) $(CFLAGS) $< -o $@

image.elf : startup.o swi.o vectors.o frame.o main.o
	$(LD) $(LDFLAGS) $^ $(LIBRARIES) -o $@

image.bin : image.elf
	$(OBJCOPY) -O binary $< $@

rundebug: image.elf
	QEMU_AUDIO_DRV=none qemu-system-arm -s -S -M versatilepb -m 128M -nographic -kernel image.elf -serial stdio
run: image.elf
	QEMU_AUDIO_DRV=none qemu-system-arm -M versatilepb -m 128M -nographic -kernel image.elf -serial stdio

clean :
	rm -f *.o image.bin image.elf
