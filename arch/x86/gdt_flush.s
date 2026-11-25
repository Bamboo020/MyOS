BITS 32

section .text

global gdt_flush

gdt_flush:
        mov eax, [esp + 4] ;Get the address of GDTPointer
        lgdt [eax]          ;Load the new GDT

        ;Load the kernel data segment selector
        mov ax, 0x10
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        mov ss, ax

        ;Reload the code segment register
        jmp 0x08:flush_cs

flush_cs:

        ;Return to the C++ caller
        ret


