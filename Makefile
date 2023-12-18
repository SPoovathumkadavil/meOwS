#NOTE: $@ is right of the :, and $< is the left
MAKEFLAGS = -s #silent

# Locations
SRC_DIR = ./src/kernel
BIN_DIR = ./bin
OBJ_DIR = ./build
INCL_DIR = ./src/include

ASM_SRC_FILES := $(wildcard $(SRC_DIR)/*.asm) $(wildcard $(SRC_DIR)/*/*.asm) $(wildcard $(SRC_DIR)/*/*/*.asm)
CPP_SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp) $(wildcard $(SRC_DIR)/*/*/*.cpp)
C_SRC_FILES := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*/*/*.c)

#Put all the files together in one list
#This is now a single list of every file that needs to be compiled together
SRC_FILES := $(ASM_SRC_FILES) $(C_SRC_FILES) $(CPP_SRC_FILES)

OBJ_FILES := $(subst $(SRC_DIR), $(OBJS_DIR), $(addsuffix .o, $(basename $(SRC_FILES))))

OUT_BIN_FILE = $(BIN_DIR)/os.bin

COMMON_FLAGS = -ffreestanding -O2

CC = i386-elf-gcc
CFLAGS = -std=gnu17 $(COMMON_FLAGS)
CPP = i686-elf-c++
CPPFLAGS = -fno-exceptions -std=c++17 $(COMMON_FLAGS) -fno-rtti

LDFLAGS = -T src/linker.ld $(COMMON_FLAGS) -nostdlib -lgcc

ASM = nasm
ASMFLAGS = -felf32 -F dwarf -g

ISO_FILE = meows.iso

build : $(OUT_BIN_FILE)

$(OUT_BIN_FILE) : $(OBJ_FILES)
	$(CC) $(LDFLAGS) $(OBJ_FILES) -o $(OUT_BIN_FILE)
	echo "Linking $(OBJ_FILES) ----------> $@"

# assemble any .asm files and put them in the OBJS_DIR
$(OBJS_DIR)/%.o : $(SRC_DIR)/%.asm
	mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) $< -o $@
	echo "$<  ----->  $@"

#compile any .c files and put them in the OBJS_DIR
$(OBJS_DIR)/%.o : $(SRC_DIR)/%.c 
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@
	echo "$<  ----->  $@"

#compiile and .cpp files and put them in the OBJS_DIR
$(OBJS_DIR)/%.o : $(SRC_DIR)/%.cpp 
	mkdir -p $(dir $@)
	$(CPP) $(CPPFLAGS) $< -o $@
	echo "$<  ----->  $@"

files: 
	echo "<----- .asm ----->"
	echo $(ASM_SRC_FILES) "\n"
	echo "<----- .c ----->"
	echo $(C_SRC_FILES) "\n"
	echo "<----- .cpp ----->"
	echo $(CPP_SRC_FILES)  "\n"
	echo "<----- objects ----->"
	echo $(OBJ_FILES) "\n"
	echo "<----- Output File ----->"
	echo $(OUTPUT_FILE)

#.PHONY tells make that there will never be these files
.PHONY: clean print run all list files

rebuild: print clean build buildiso
	echo "Full Clean and Make done..."

all: rebuild run

clean:
	echo "Clean up..."
	rm -rf $(OBJS_DIR)

	rm -f $(BIN_DIR)/*~ $(BIN_DIR)/*.bin $(BIN_DIR)/*.iso

ISODIR = isodir/boot/grub
ISOBOOTDIR = isodir/boot

buildiso:
	mkdir -p $(ISODIR)
	cp $(OUT_BIN_FILE) $(ISOBOOTDIR)/meows.bin
	cp src/grub.cfg $(ISODIR)/grub.cfg
	grub-mkrescue -o $(BIN_DIR)/meows.iso isodir
	echo "ISO Made :D"

print:
	# don't fail if figlet isn't installed
	if which figlet >/dev/null; then figlet -c MeowS; else echo "                        ##### MeowS #####"; fi
	
run:
	echo "Starting QEMU"
	#qemu-system-i386 -kernel $(OUTPUT_FILE) -serial stdio
	qemu-system-i386 -cdrom $(BIN_DIR)/$(ISO_FILE)
