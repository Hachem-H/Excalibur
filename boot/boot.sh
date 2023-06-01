nasm -f bin -o bin/boot.bin boot/boot.asm
xxd -i bin/boot.bin > Excalibur-Installer/src/Boot.h