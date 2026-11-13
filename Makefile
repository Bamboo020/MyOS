
# Compiler and assembler
CXX = g++
ASM = nasm
LD = ld

# Compiler flags
CXXFLAGS = -m32 -std=c++17 -ffreestanding \
           -fno-exceptions -fno-rtti \
           -fno-stack-protector -fno-pie \
           -fno-asynchronous-unwind-tables \
           -fno-unwind-tables \
           -O2 -Wall -Wextra

# Default target
all: kernel.elf

# Compile assembly
load/loader.o: load/loader.s
	$(ASM) -f elf32 load/loader.s -o load/loader.o

# Compile C++
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# Link kernel
kernel.elf: load/loader.o main.o link/link.ld
	$(LD) -m elf_i386 -T link/link.ld \
	-o kernel.elf load/loader.o main.o

# Copy kernel to ISO directory
iso/boot/kernel.elf: kernel.elf
	cp kernel.elf iso/boot/kernel.elf

# Create bootable ISO
myos.iso: iso/boot/kernel.elf iso/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso iso

# Run in QEMU with SDL
run: myos.iso
	qemu-system-i386 -cdrom myos.iso -boot d -m 128 -display sdl

# Remove generated files
clean:
	rm -f load/loader.o main.o kernel.elf
	rm -f iso/boot/kernel.elf myos.iso

.PHONY: all run clean
