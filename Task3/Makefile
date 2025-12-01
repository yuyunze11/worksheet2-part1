#工具
CC      := gcc
LD      := ld
ASM     := nasm

#编译参数
CFLAGS  := -m32 -ffreestanding -O2 -Wall -Wextra \
           -fno-stack-protector -fno-pic -nostdlib
ASFLAGS := -f elf32
LDFLAGS := -m elf_i386

SRCDIR  := source
DRVDIR  := drivers
ISODIR  := iso

KERNEL  := kernel.elf
ISO     := os.iso

OBJS    := loader.o io.o fb.o kmain.o

.PHONY: all kernel iso run run-kernel clean

# 默认：生成内核
all: kernel

kernel: $(KERNEL)

# 链接生成 kernel.elf
$(KERNEL): $(OBJS) $(SRCDIR)/link.ld
	$(LD) $(LDFLAGS) -T $(SRCDIR)/link.ld -o $@ $(OBJS)

# 汇编 → .o
loader.o: $(SRCDIR)/loader.asm
	$(ASM) $(ASFLAGS) $< -o $@

io.o: $(SRCDIR)/io.asm
	$(ASM) $(ASFLAGS) $< -o $@

# C → .o
fb.o: $(DRVDIR)/fb.c $(DRVDIR)/fb.h $(SRCDIR)/io.h
	$(CC) $(CFLAGS) -c $< -o $@

kmain.o: $(SRCDIR)/kmain.c $(DRVDIR)/fb.h
	$(CC) $(CFLAGS) -c $< -o $@

# 生成 ISO
iso: $(ISO)

$(ISO): $(KERNEL) $(ISODIR)/boot/grub/menu.lst $(ISODIR)/boot/grub/stage2_eltorito
	mkdir -p $(ISODIR)/boot/grub
	cp $(KERNEL) $(ISODIR)/boot/kernel.elf
	mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot \
		-boot-load-size 4 -boot-info-table \
		-o $(ISO) $(ISODIR)

# 直接用 kernel.elf 跑（不走 GRUB）
run-kernel: $(KERNEL)
	qemu-system-i386 -display curses -kernel $(KERNEL) -m 32

# 走 os.iso + GRUB 再进内核
run: $(ISO)
	qemu-system-i386 -display curses -boot d -cdrom $(ISO) -m 32

# 清理
.PHONY: clean

clean:
	rm -f loader.o io.o fb.o kmain.o \
	      kernel.elf os.iso logQ.txt


