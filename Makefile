
# ==========================================
# 1. Tools
# ==========================================
CXX = g++
ASM = nasm
LD = ld

# ==========================================
# 2. Compiler Flags
# ==========================================
CXXFLAGS = -m32 -std=c++17 -ffreestanding \
           -fno-exceptions -fno-rtti \
           -fno-stack-protector -fno-pie \
           -fno-asynchronous-unwind-tables \
           -fno-unwind-tables \
           -O2 -Wall -Wextra \
           -I. -MMD -MP

ASMFLAGS = -f elf32

LDFLAGS = -m elf_i386 -T link/link.ld

# ==========================================
# 3. Source Files
# ==========================================
CPP_SOURCES = kernel/main.cpp \
              drivers/vga/cursor.cpp \
              drivers/vga/framebuffer.cpp \
			  serial/serial.cpp

ASM_SOURCES = load/loader.s \
              arch/x86/io.s

# ==========================================
# 4. Object Files
# ==========================================
CPP_OBJECTS = $(patsubst %.cpp,build/%.o,$(CPP_SOURCES))
ASM_OBJECTS = $(patsubst %.s,build/%.o,$(ASM_SOURCES))

OBJECTS = $(ASM_OBJECTS) $(CPP_OBJECTS)
DEPENDS = $(CPP_OBJECTS:.o=.d)

# ==========================================
# 5. Default Target
# ==========================================
all: kernel.elf

# ==========================================
# 6. Compile C++ Files
# ==========================================
build/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ==========================================
# 7. Compile Assembly Files
# ==========================================
build/%.o: %.s
	mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) $< -o $@

# ==========================================
# 8. Link Kernel
# ==========================================
kernel.elf: $(OBJECTS) link/link.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS)

# ==========================================
# 9. Copy Kernel to ISO Directory
# ==========================================
iso/boot/kernel.elf: kernel.elf
	mkdir -p iso/boot
	cp kernel.elf iso/boot/kernel.elf

# ==========================================
# 10. Create Bootable ISO
# ==========================================
myos.iso: iso/boot/kernel.elf iso/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso iso

# ==========================================
# 11. Run in QEMU
# ==========================================
run: myos.iso
	qemu-system-i386 -cdrom myos.iso \
	    -boot d -m 128 -display sdl

# ==========================================
# 12. Clean Build Files
# ==========================================
clean:
	rm -rf build
	rm -f kernel.elf myos.iso
	rm -f iso/boot/kernel.elf

# ==========================================
# 13. Header Dependencies
# ==========================================
-include $(DEPENDS)

.PHONY: all run clean
