%ifdef __BOOT_DEBUG__
    org     0x0100          ; boot from 0000:0100
%else
    org     0x7C00          ; boot from 0000:7C00
%endif

    mov     ax, cs
    mov     ds, ax
    mov     es, ax
    call    prints

    jmp     $

prints:
    mov     ax, boot_msg
    mov     bp, ax          ; es:bp -> offset of string
    mov     cx, 13          ; string length
    mov     ah, 0x13        ; write string to the screen
    mov     al, 0x01        ; write mode (string is chars only, attribute in BL, cursor moved)
    mov     bh, 0x00        ; the page number
    mov     bl, 0x0F        ; the color of text
    mov     dh, 0x00        ; row number
    mov     dl, 0x00        ; column number
    int     0x10            ; BIOS Video Display Services
    ret

boot_msg:               db  "Hello, Koala!"

times       510-($-$$)  db  0

dw          0xaa55
