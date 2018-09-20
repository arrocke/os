# DIRECTORIES
# The directory where all generated files are stored.
BUILD_DIR=build
# The build directory for all object files.
OBJ_DIR=$(BUILD_DIR)/obj
# The build directory for log files.
LOG_DIR=$(BUILD_DIR)/log
# The build directory for iso files.
ISO_DIR=$(BUILD_DIR)/iso
# The directory for C header files.
INCLUDE_DIR=include
# The directory for C and ASM source files.
SRC_DIR=src

# FILE NAMES
# The operating system disk image.
ISO=$(BUILD_DIR)/os.iso
# The binary kernel elf file.
KERNEL=$(BUILD_DIR)/kernel.elf
# The C and ASM source file names.
FILES=loader kmain fb serial io log gdt gdt_asm
# The C and ASM object files.
OBJECTS=$(patsubst %, $(OBJ_DIR)/%.o, $(FILES))

# COMPILER
# The C compiler executable.
CC=gcc
# The flags for compiling C source code.
CFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -fomit-frame-pointer \
		-Wno-unused-function -c
# The flags for linking object files.
LDFLAGS=-T link.ld -melf_i386
# The ASM compiler executable.
AS=nasm
# The flags for compiling ASM source code.
ASFLAGS=-f elf

# BUILD TARGETS
# Default recipe
# Builds the kernel.
build: init $(ISO)

# Run the OS emulator.
run: $(ISO)
	bochs -f bochsrc.txt -q

# Initializes the build environment.
init:
	mkdir -p build
	mkdir -p build/log
	mkdir -p build/obj

# Removes the build directories.
clean:
	rm -rf $(BUILD_DIR)/*

# FILE RECIPIES
# Link the kernel from object files.
$(KERNEL): $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o $@ 

# Builds the ISO from the compiled kernel.
$(ISO): $(KERNEL)
	mkdir -p $(ISO_DIR)/boot/grub
	cp menu.lst $(ISO_DIR)/boot/grub/
	cp stage2_eltorito $(ISO_DIR)/boot/grub/
	cp $(KERNEL) $(ISO_DIR)/boot/
	genisoimage -R                              \
				-b boot/grub/stage2_eltorito    \
				-no-emul-boot                   \
				-boot-load-size 4               \
				-A os                           \
				-input-charset utf8             \
				-quiet                          \
				-boot-info-table                \
				-o $@                      	    \
				$(ISO_DIR)


# Compiles object files from C source code.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) $< -o $@

# Compiles object files from ASM source code.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	$(AS) $(ASFLAGS) -I $(INCLUDE_DIR) $< -o $@
