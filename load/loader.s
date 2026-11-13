
global loader
extern kernel_main

MAGIC_NUMBER equ 0x1BADB002
FLAGS        equ 0x0
CHECKSUM     equ -MAGIC_NUMBER

section .text
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

loader:
    cli                     ; Disable interrupts
    cld                     ; Clear direction flag

    mov esp, stack_top      ; Initialize stack

    call kernel_main        ; Call C++ function

.loop:
    hlt                     ; Halt CPU
    jmp .loop               ; Infinite loop

section .bss
align 16

stack_bottom:
    resb 16384              ; Reserve 16 KB

stack_top: