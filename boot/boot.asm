%ifdef __BOOT_DEBUG__
    org     0x0100          ; boot from 0000:0100
%else
    org     0x7C00          ; boot from 0000:7C00
%endif

    call    scrnloc

    mov     ax, cs
    mov     ds, ax
    mov     es, ax
    mov     ax, boot_msg
    mov     cx, boot_msg_len
    call    prints

    jmp     $

%include "../lib/print.inc"
%include "../lib/screen.inc"

boot_msg:               db  "Hello, Koala!"
boot_msg_len:           equ $-boot_msg

times       510-($-$$)  db  0

dw          0xaa55
