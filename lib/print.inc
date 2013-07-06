;
; Print character, number, string on screen
;


;
; Print character by BIOS
; 
; @param al
;           the character
;
printc:
    pusha
    push    eax

    cmp     eax, 0x0A       ; if (eax != '\n')
    jne     .locate         ;     goto .locate

    mov     eax, [row]
    inc     eax
    mov     [row], eax
    mov     eax, 0
    mov     [col], eax

.locate:
    mov     ah, 0x02        ; Set cursor position
    mov     bh, 0x00        ; page number
    mov     dh, [row]       ; cursor row
    mov     dl, [col]       ; cursor column
    int     0x10            ; BIOS Video Display Services

.print:
    pop     eax             ; character to be print
    cmp     eax, 0x0A       ; if (eax == '\n')
    je      .done

    mov     ah, 0x0a        ; Write character only at cursor position
    mov     bh, 0x00        ; page number
    mov     cx, 0x01        ; number of times to print
    int     0x10            ; BIOS Video Display Services

    mov     eax, [col]      ;
    inc     eax             ; col++
    mov     [col], eax      ;

    cmp     eax, [scrnw]    ; if (col < scrnw)
    jl      .done           ;     goto .done

    mov     edx, 0
    mov     ebx, [scrnw]
    idiv    ebx             ; eax = eax / scrnw; edx = eax % scrnw
    add     [row], eax      ; row += eax
    mov     [col], edx      ; col += edx

.done:
    popa
    ret

;
; Print integer by BIOS
; 
; @param sp
;           the integer value
;
printd:
    pusha

    mov     ebx, 10         ; divider
    mov     ecx, 0          ; digits counter

.count_digit:
    mov     edx, 0          ; clear edx
    idiv    ebx             ; eax=eax / ebx
    push    edx             ; edx=eax % ebx
    inc     ecx

    cmp     eax, 0
    jnz     .count_digit

.print_digit:
    pop     edx
    add     edx, '0'
    mov     eax, edx
    call    printc

    dec     ecx
    cmp     ecx, 0
    jnz     .print_digit

    popa
    ret

;
; Print string by BIOS
; 
; @param ax
;           the string to be print
; @param cx
;           the length of string
;
prints:
    mov     bp, ax          ; es:bp -> offset of string
    mov     ah, 0x13        ; write string to the screen
    mov     al, 0x01        ; write mode (string is chars only, attribute in BL, cursor moved)
    mov     bh, 0x00        ; the page number
    mov     bl, 0x0F        ; the color of text
    mov     dh, [row]       ; row number
    mov     dl, [col]       ; column number
    int     0x10            ; BIOS Video Display Services

    add     [col], cx       ;

    ret

;
; Print end-of-line by BIOS
;
println:
    pusha

    mov     eax, 0x0A
    call    printc

    popa
    ret

