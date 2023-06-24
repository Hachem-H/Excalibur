[bits 16]
[org 0x7C00]

%define WIDTH  320
%define HEIGHT 200

%define VELOCITY 2

struc Quad_t
    .x:      resw 1
    .y:      resw 1
    .width:  resw 1
    .height: resw 1
    .color:  resb 1
endstruc

Quad: istruc Quad_t
    at Quad_t.x,      dw WIDTH/2
    at Quad_t.y,      dw HEIGHT/2
    at Quad_t.width,  dw 30
    at Quad_t.height, dw 20
    at Quad_t.color,  db 12
iend

velocity.x: dw 0x00
velocity.y: dw 0x00

Initialize:
    mov bp, sp
    mov ax, 13h
    int 0x10

    mov ax, 0xA0000/16
    mov es, ax

    mov WORD [velocity.x], VELOCITY
    mov WORD [velocity.y], VELOCITY

GameLoop:
    mov ax, Quad
    call RenderQuad
    call Sleep
    
    mov ax, [Quad + Quad_t.x]
    mov ax, [Quad + Quad_t.width]
    cmp ax, WIDTH
    jge right

    mov ax, [Quad + Quad_t.x]
    mov ax, [Quad + Quad_t.width]
    cmp ax, 0x00
    jle left

    jmp NextX

    right:
        mov WORD [velocity.x], -VELOCITY
        jmp NextX
    left:
        mov WORD [velocity.x], VELOCITY

    NextX:
        mov ax, [Quad + Quad_t.y]
        add ax, [Quad + Quad_t.height]
        cmp ax, HEIGHT
        jge up

        mov ax, [Quad + Quad_t.y]
        sub ax, [Quad + Quad_t.height]
        cmp ax, 0x00
        jle down
        
        jmp NextY
    
    up:
        mov WORD [velocity.y], -VELOCITY
        jmp NextY
    down:
        mov WORD [velocity.y], VELOCITY
    NextY:

    mov BYTE [Quad + Quad_t.color], 0x00
    mov ax, Quad

    call RenderQuad
    call VerticalBlank
    
    mov ax, WORD [velocity.x]
    add WORD [Quad + Quad_t.x], ax
    mov ax, WORD [velocity.y]
    add WORD [Quad + Quad_t.y], ax

jmp GameLoop
jmp $

Sleep:
    pusha
    mov al, 0x0000
    mov ah, 0x0086
    mov dx, 0xAFFF
    mov cx, 0x0009
    int 0x15
    clc
    popa
    ret

RenderQuad:
    push bp
    mov bp, sp
    mov bx, ax

    mov ax, [bx + Quad_t.x]
    add ax, [bx + Quad_t.width]
    push ax
    mov ax, [bx + Quad_t.x]
    sub ax, [bx + Quad_t.width]
    push ax
    mov ax, [bx + Quad_t.y]
    add ax, [bx + Quad_t.height]
    push ax
    mov ax, [bx + Quad_t.y]
    sub ax, [bx + Quad_t.height]
    push ax

    mov dx, [bx + Quad_t.color]
    mov bx, [bp - 8]

    Vertical:
        mov ax, [bp - 4]
        mov di, bx
        imul di, 320
        add di, [bp - 4]
    Horizontal:
        mov BYTE es:[di], dl
        inc di

        inc ax
        cmp ax, [bp - 2]
        jne Horizontal

        inc bx
        cmp bx, [bp - 6]
        jne Vertical

    leave
    ret

VerticalBlank:
    mov dx, 0x03DA
    .EqRet:
        in al, dx
        test al, 8
        je .EqRet
    .NeqRet:
        in al, dx
        test al, 8
        je .NeqRet
    ret

times 510-($-$$) db 0x00
dw 0xAA55









