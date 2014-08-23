OBJDIR=obj
AS=arm-none-eabi-as
CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
OBJCOPY=arm-none-eabi-objcopy
CPU=cortex-a8
CFLAGS=-g -Iinclude/ -Wall
ASFLAGS=-g
LDFLAGS=-T src/kernel.ld -L$(OBJDIR)/
LIBRARIES=-lkyubey

$(OBJDIR)/%.o : src/%.s
	$(AS) -mcpu=$(CPU) $(ASFLAGS) $< -o $@
$(OBJDIR)/%.o : src/%.c
	$(CC) -c -mcpu=$(CPU) $(CFLAGS) $< -o $@

$(OBJDIR)/%.o : lib/%.s
	$(AS) -mcpu=$(CPU) $(ASFLAGS) $< -o $@
$(OBJDIR)/%.o : lib/%.c
	$(CC) -c -mcpu=$(CPU) $(CFLAGS) $< -o $@

tftp: uImage
	cp uImage /srv/tftp/
	chmod 644 /srv/tftp/uImage
	sudo ifconfig enp2s0 10.0.0.1

uImage: image.bin
	mkimage -A arm -T kernel -C none -a 80300000 -e 80300000 -n octocabbit -d image.bin uImage

copy: uImage
	mount /mnt
	cp uImage /mnt
	sync
	umount /mnt

image.bin : image.elf
	$(OBJCOPY) -O binary $< $@

image.elf : $(OBJDIR)/libkyubey.a $(addprefix $(OBJDIR)/, startup.o swi.o vectors.o dumpregs.o switch.o main.o)
	$(LD) $(LDFLAGS) $^ $(LIBRARIES) -o $@

$(OBJDIR)/libkyubey.a : $(addprefix $(OBJDIR)/, kputs.o kprintf.o khexdump.o memcpy.o)
	$(AR) rv $@ $^

clean:
	rm -f image.bin image.elf uImage obj/*
