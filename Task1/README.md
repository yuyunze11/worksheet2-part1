 # Menu.lst
  ``` asm
default=0              # default to the 0th menu entry
timeout=0              # do not wait, boot immediately

title Task1 OS         # title of the menu entry
kernel /boot/kernel.elf    # path to the kernel file to load (path inside the ISO)
```
  Tell GRUB which kernel to boot, load the kernel according to kernel /boot/kernel.elf, check the Multiboot header in kernel.elf, and jump to our loader label to start execution
 ```
``` 
 # Loader
``` asm

 global loader                          ; kernel entry point

;Multiboot header definition
MAGIC_NUMBER  equ 0x1BADB002           ; Multiboot magic number, used by GRUB to recognize the kernel
FLAGS         equ 0x0                  ; Multiboot flags, no extra requirements here
CHECKSUM      equ -MAGIC_NUMBER        ; checksum: MAGIC + FLAGS + CHECKSUM must equal 0

section .text                          ; code section
align 4                                ; align to 4 bytes
    dd MAGIC_NUMBER                    ; write magic number for GRUB to read
    dd FLAGS                           ; flags
    dd CHECKSUM                        ; checksum, checked by GRUB

;kernel entry

loader:                                ; kernel entry point, GRUB jumps here to start execution
    mov eax, 0xCAFEBABE                ; load a special constant into EAX

.loop:                                 ; infinite loop label
    jmp .loop                          ; infinite loop to keep EAX at 0xCAFEBABE
```
  GRUB loads correctly and jumps into the loader, executes mov eax, 0xCAFEBABE, and EAX no longer changes in the infinite loop.EAX=cafebabe will keep appearing in QEMU's CPU log.
 # Kernel Entry Point

 ``` asm
loader:
    mov eax, 0xCAFEBABE
 ```
   Write a minimal kernel with a Multiboot header so that GRUB can recognize and load it, then write a kernel entry point, build a bootable ISO image containing GRUB and the kernel, and finally use QEMU's CPU logs to check the register status.
 ```