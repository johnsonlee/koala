;
; Screen & Cursor utilities
;

row:        dd      0        ; The row number of cursor on screen

col:        dd      0        ; The column number of cursor on screen

scrnw:      dd      80

;
; Locate cursor position on screen
;
scrnloc:
    pusha

    mov     ah, 0x03        ; get cursor position and shape
    mov     bh, 0x00        ; page number
    int     0x10

    mov     [row], dh
    mov     [col], dl
    popa
    ret

