AS=arm-none-eabi-as
CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
OBJCOPY=arm-none-eabi-objcopy
CPU=cortex-a8
CFLAGS=-g -I../include/ -Wall
ASFLAGS=-g
LDFLAGS=-T kernel.ld -L../lib/
LIBRARIES=-lkyubey

%.o : %.s
	$(AS) -mcpu=$(CPU) $(ASFLAGS) $< -o $@
%.o : %.c
	$(CC) -c -mcpu=$(CPU) $(CFLAGS) $< -o $@

copy: uImage
	mount /mnt
	cp uImage /mnt
	sync
	umount /mnt

uImage: image.bin
	mkimage -A arm -T kernel -C none -a 80300000 -e 80300000 -n octocabbit -d image.bin uImage

image.bin : image.elf
	$(OBJCOPY) -O binary $< $@

image.elf : startup.o swi.o vectors.o dumpregs.o switch.o main.o
	$(LD) $(LDFLAGS) $^ $(LIBRARIES) -o $@


clean:
	rm -f *.o image.bin image.elf uImage
