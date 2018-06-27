global gdt_load

SEGSEL_KERNEL_CS equ 0x08       ; The GDT segment table index for code
SEGSEL_KERNEL_DS equ 0x10       ; The GDT segment table index for data

; load the gdt into the cpu, and enter the kernel segments
gdt_load:
    mov     eax, [esp+4]        ; fetch gdt_ptr from parameter stack
    lgdt    [eax]               ; load gdt table

    ; load cs segment by doing a far jump
    jmp     SEGSEL_KERNEL_CS:.reload_segments

.reload_segments:
    ; we only use one segment for data
    mov     ax, SEGSEL_KERNEL_DS
    mov     ds, ax
    mov     ss, ax
    mov     es, ax
    mov     gs, ax
    mov     fs, ax
    ret