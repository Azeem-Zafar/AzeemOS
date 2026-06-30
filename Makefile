all: os.img

boot/boot.bin:
	nasm -f bin boot/boot.asm -o boot/boot.bin

src/kernel.o:
	gcc -m32 -ffreestanding -fno-pie -c src/kernel.c -o src/kernel.o

src/kernel.bin: src/kernel.o
	ld -m elf_i386 -T src/linker.ld -o src/kernel.bin src/kernel.o --oformat binary

os.img: boot/boot.bin src/kernel.bin
	cat boot/boot.bin src/kernel.bin > os.img

run: os.img
	qemu-system-x86_64 -drive format=raw,file=os.img,if=floppy

clean:
	rm -f boot/boot.bin src/kernel.o src/kernel.bin os.img
