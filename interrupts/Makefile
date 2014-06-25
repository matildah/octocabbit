AS=arm-none-eabi-as
CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
OBJCOPY=arm-none-eabi-objcopy
CPU=arm926ej-s
CFLAGS=-g
ASFLAGS=-g
LDFLAGS=-T startup.ld

%.o : %.s
	$(AS) -mcpu=$(CPU) $(ASFLAGS) $< -o $@
%.o : %.c
	$(CC) -c -mcpu=$(CPU) $(CFLAGS) $< -o $@

image.elf : startup.o main.o
	$(LD) $(LDFLAGS) $^ -o $@

image.bin : image.elf
	$(OBJCOPY) -O binary $< $@

rundebug: image.elf
	qemu-system-arm -s -S -M versatilepb -m 128M -nographic -kernel image.elf -serial stdio
run: image.elf
	qemu-system-arm -M versatilepb -m 128M -nographic -kernel image.elf -serial stdio

clean :
	rm -f *.o image.bin image.elf
