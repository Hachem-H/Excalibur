.PHONY: boot

boot:
	nasm -f bin -o boot.bin boot/boot.asm
	xxd -i boot.bin > src/Boot.h
	rm boot.bin
