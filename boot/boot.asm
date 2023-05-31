[bits 16]
[org 0x7C00]

jmp $

times 510-($-$$) db 0x00
dw 0xAA55
