; Credit to https://github.com/portasynthinca3/bootsect/

[org 0x7C00]
[bits 16]

%define WaitTime 0x7E00

Entry:
    xor ah, ah
    mov al, 0x13
    int 0x10
    mov ax, 0xA000
    mov fs, ax

    mov cx, 0x83
    xor bx, bx
    mov dl, 0x35
    call RenderBackground

    mov cx, 0x45
    mov bx, 0x83
    inc dl
    call RenderBackground

    mov si, FoamSprite
    mov dh, 0x80
    mov dl, 0xF
    xor bx, bx
    mov cx, 0xD
    .foam:
        call RendererQuad
        add bx, 0x18
        loop .foam

    mov cx, 0x01
    mov bx, 0x82
    call RenderBackground

    mov cl, BYTE [FishPositions]
    xor di, di
    mov dl, 0x37
    .fish:
        mov si, WORD [FishPositions+di+0x1]
        mov bx, WORD [FishPositions+di+0x3]
        mov dh, BYTE [FishPositions+di+0x5]
        add di, 0x06
        call RendererQuad
        loop .fish


    mov ax, 0x4A9
    out 0x40, al
    mov al, ah
    out 0x40, al

    mov ax, cs
    mov WORD [0x0022], ax
    mov WORD [0x0020], irq0
    jmp $

irq0:
    inc WORD [WaitTime]
    cmp WORD [WaitTime], 0x3E8
    jb .NoOverflow
    mov WORD [WaitTime], 0x000
       
    .NoOverflow:
        mov ax, WORD [WaitTime]
        cmp ax, 0xFA
        jne .NoSTR
        mov bx, 0x80
        call ShiftRowRight
    .NoSTR:
        cmp ax, 0x2EE
        jne .NoSTL
        mov bx, 0x80
        call ShiftRowLeft
    .NoSTL:
        cmp ax, 0x1F4
        jne .NoSbr
        mov bx, 0x83
        call ShiftRowRight
        mov bx, 0x81
        call ShiftRowRight
    .NoSbr:
        cmp ax, 0x3E7
        jne .NoSBL
        mov bx, 0x83
        call ShiftRowLeft
        mov bx, 0x81
        call ShiftRowLeft
    .NoSBL:
        push ax
        mov bl, 0x32
        div bl
        cmp ah, 0x00
        jne .NotFish
        mov bx, 0x8A
        mov cx, 0x0B
        call ShiftQuadLeft
    .NotFish:
        pop ax
        mov bl, 0x46
        div bl
        cmp ah, 0x00
        jne .NoBottomFish
        mov bx, 0x9D
        mov cx, 0x1D
        call ShiftQuadLeft
    .NoBottomFish:
        mov al, 0x20
        out 0x20, al
    iret

RenderBackground:
    push dx

    mov ax, 0x140
    add bx, cx
    mul bx
    mov di, ax

    mov ax, cx
    mov dx, 0x140
    mul dx
    mov cx, ax

    pop dx
    .iter:
        dec di
        mov BYTE [fs:di], dl
        loop .iter
    ret

ShiftRowRight:
    push ax
    push cx
    push dx
    mov ax, 0x140
    inc bx
    mul bx
    mov di, ax
    mov cx, 0x13F
    .iter:
        dec di
        mov al, BYTE [fs:di-1]
        mov BYTE [fs:di], al
        loop .iter
    pop dx
    pop cx
    pop ax
    ret
ShiftRowLeft:
    push ax
    push cx
    push dx
    mov ax, 0x140
    mul bx
    mov di, ax
    mov cx, 0x13F
    .iter:
        mov al, BYTE [fs:di+1]
        mov BYTE [fs:di], al
        inc di
        loop .iter

    mov al, BYTE [fs:di-0x13F]
    mov BYTE [fs:di], al
    pop dx
    pop cx
    pop ax
    ret
ShiftQuadLeft:
    .iter:
        call ShiftRowLeft
        inc bx
        loop .iter
    ret

RendererQuad:
    push si
    push cx
    push di
    push ax

    mov al, dh
    mov cl, 0xA0
    mul cl
    shl ax, 0x01
    mov di, ax
    add di, bx

    mov al, BYTE [si]
    movzx cx, al
    and cx, 0x0F

    shr al, 0x04
    inc si
    push ax

    .row:
        pop ax
        push ax
        .chunk:
            mov ah, BYTE [si]
            mov bp, 0x08

            .pixel:
                test ah, 0x80
                jz .BackgroundPixel
                mov BYTE [fs:di], dl
                .BackgroundPixel:
                    shl ah, 0x01
                    inc di
                    dec bp
                    jnz .pixel
            inc si
            dec al
            jnz .chunk

        pop ax
        add di, 0x140
        shl al, 0x003
        xor ah, ah
        sub di, ax
        shr al, 0x003
        push ax
        loop .row

    .return:
        pop ax
        pop ax
        pop di
        pop cx
        pop si
        ret

FoamSprite:
    db (3 << 4) | (4 << 0)
    db 00011100b, 00000000b, 00000000b
    db 01111110b, 00000011b, 00001110b
    db 11111111b, 11111111b, 11111111b
    db 00000000b, 00011111b, 11000000b
SmallFish:
    db (3 << 4) | (6 << 0)
    db 00111110b, 00001101b, 10000000b
    db 01111111b, 11100111b, 00000000b
    db 11011111b, 11111110b, 00000000b
    db 11111111b, 11111100b, 00000000b
    db 01111111b, 11111000b, 00000000b
    db 00111111b, 11100000b, 00000000b
CoralFish:
    db (1 << 4) | (8 << 0)
    db 00010000b
    db 00110010b
    db 01110010b
    db 10111110b
    db 11111110b
    db 01110110b
    db 00110010b
    db 00010000b

FishPositions:
    db 10
    dw SmallFish,  54, 159
    dw SmallFish, 121, 143
    dw SmallFish, 252, 140
    dw SmallFish, 169, 157
    dw SmallFish,  78, 180
    dw SmallFish, 152, 176
    dw CoralFish,  92, 157
    dw CoralFish,  80, 138
    dw CoralFish, 217, 160
    dw CoralFish, 233, 173

times 510-($-$$) db 0x00
dw 0xAA55
