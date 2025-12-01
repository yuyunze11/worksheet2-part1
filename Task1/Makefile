NASM= nasm
LD = ld
GENISO = genisoimage
QEMU = qemu-system-i386

LOADER_SRC = source/loader.asm
LOADER_OBJ = source/loader.o
KERNEL_ELF = iso/boot/kernel.elf
LINKER_SCRIPT = source/link.ld
ISO_IMAGE = os.iso 

NASM_FLAGS = -f elf
LD_FLAGS = -T $(LINKER_SCRIPT) -melf_i386
GENISO_FLAGS = -R -b boot/grub/stage2_eltorito -no-emul-boot \
	-boot-load-size 4 -A os -input-charset utf8 \
	-quiet -boot-info-table
QEMU_FLAGS =  -nographic -boot d -cdrom $(ISO_IMAGE) -m 32 -d cpu -D logQ.txt

all: $(ISO_IMAGE)

$(LOADER_OBJ): $(LOADER_SRC)
	$(NASM) $(NASM_FLAGS) $< -o $@

$(KERNEL_ELF): $(LOADER_OBJ)
	$(LD) $(LD_FLAGS) $< -o $@

$(ISO_IMAGE): $(KERNEL_ELF)
	$(GENISO) $(GENISO_FLAGS) -o $@ iso

run: $(ISO_IMAGE)
	$(QEMU) $(QEMU_FLAGS)

clean:
	rm -f $(LOADER_OBJ) $(KERNEL_ELF) $(ISO_IMAGE) logQ.txt


.PHONY: all run clean
