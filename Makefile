# Directories
BUILD_DIR=build
OBJ_DIR=$(BUILD_DIR)/obj
LOG_DIR=$(BUILD_DIR)/log
ISO_DIR=$(BUILD_DIR)/iso
INCLUDE_DIR=include
SRC_DIR=src

# Build targets
ISO=$(BUILD_DIR)/os.iso
KERNEL=$(BUILD_DIR)/kernel.elf
FILES=loader kmain fb serial io log
OBJECTS=$(patsubst %, $(OBJ_DIR)/%.o, $(FILES))

# Compiler settings
CC=gcc
CFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -fomit-frame-pointer \
		-Wno-unused-function -c
LDFLAGS=-T link.ld -melf_i386
AS=nasm
ASFLAGS=-f elf

# Default recipe
build: init $(KERNEL)

# Run the OS emulator
run: $(ISO)
	bochs -f bochsrc.txt -q

# Compile the kernel
$(KERNEL): $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o $@ 

# Build the ISO
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

# Initialize the build environment
init:
	mkdir -p build
	mkdir -p build/log
	mkdir -p build/obj

# Compile object files from c source code
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) $< -o $@

# Comple object files from assembly source code
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	$(AS) $(ASFLAGS) $< -o $@

# Clean the build directories
clean:
	rm -rf $(BUILD_DIR)/*