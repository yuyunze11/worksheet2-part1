; global loader
; extern kmain  ; 声明C语言内核入口

; ; 多重引导魔数（兼容GRUB）
; MAGIC_NUMBER equ 0x1BADB002
; FLAGS        equ 0x0
; CHECKSUM     equ -(MAGIC_NUMBER + FLAGS)

; ; 初始化内核栈（4KB，位于BSS段）
; KERNEL_STACK_SIZE equ 4096
; section .bss
; align 4
; kernel_stack:
;     resb KERNEL_STACK_SIZE  ; 预留4KB栈空间

; ; 代码段
; section .text
; align 4
;     dd MAGIC_NUMBER
;     dd FLAGS
;     dd CHECKSUM

; loader:
;     ; 设置栈指针（指向栈末尾，x86栈向低地址增长）
;     mov esp, kernel_stack + KERNEL_STACK_SIZE
;     ; 调用C语言内核入口
;     call kmain
;     ; 内核返回后死循环
; .loop:
;     jmp .loop

global loader
extern kmain

; 多重引导魔数
MAGIC_NUMBER equ 0x1BADB002
FLAGS        equ 0x0
CHECKSUM     equ -(MAGIC_NUMBER + FLAGS)

KERNEL_STACK_SIZE equ 4096
section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE

section .text
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

loader:
    ; 设置栈
    mov esp, kernel_stack + KERNEL_STACK_SIZE
    
    ; ========== 调试代码开始 ==========
    ; 直接在汇编层面写入帧缓冲区
    mov edi, 0xB8000
    mov byte [edi], 'A'        ; 在位置(0,0)显示'A' 0x41
    mov byte [edi+1], 0x07     ; 灰色背景，白色前景
    mov byte [edi+2], 'S'      ; 在位置(1,0)显示'S'
    mov byte [edi+3], 0x07
    mov byte [edi+4], 'M'      ; 在位置(2,0)显示'M'
    mov byte [edi+5], 0x07
    ; ========== 调试代码结束 ==========
    
    ; 调用C内核
    call kmain

.loop:
    jmp .loop