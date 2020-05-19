# Don't use normal gcc, use the arm cross compiler
CC = ./gcc-arm-none-eabi-9-2019-q4-major/bin/arm-none-eabi-gcc
OBJCOPY = ./gcc-arm-none-eabi-9-2019-q4-major/bin/arm-none-eabi-objcopy

# Set any constants based on the raspberry pi model. Version 1 has some differences to 2 and 3
ifeq ($(RASPI_MODEL),1)
	CPU = arm1176jzf-s
	DIRECTIVES = -D MODEL_1
else ifeq ($(RASPI_MODEL),2)
	CPU = cortex-a7
	DIRECTIVES = -D MODEL_2
else
	CPU = cortex-a7
endif


CFLAGS = -mcpu=$(CPU) -fpic -ffreestanding $(DIRECTIVES)
CSRCFLAGS = -O2 -Wall -Wextra
LDFLAGS = -ffreestanding -O2 -nostdlib

# Location of the files
KER_SRC = ../src/kernel
KER_HEAD = ../include
COMMON_SRC = ../src/common
OBJ_DIR = objects
KERSOURCES = $(wildcard $(KER_SRC)/*.c)
COMMONSOURCES = $(wildcard $(COMMON_SRC)/*.c)
ASMSOURCES = $(wildcard $(KER_SRC)/*.S)
OBJECTS = $(patsubst $(KER_SRC)/%.c, $(OBJ_DIR)/%.o, $(KERSOURCES))
OBJECTS += $(patsubst $(COMMON_SRC)/%.c, $(OBJ_DIR)/%.o, $(COMMONSOURCES))
OBJECTS += $(patsubst $(KER_SRC)/%.S, $(OBJ_DIR)/%.o, $(ASMSOURCES))
HEADERS = $(wildcard $(KER_HEAD)/*.h)

ELF_NAME=kernel.elf
IMG_NAME=kernel.img
RASPI_IMG=kernel7.img

build: $(OBJECTS) $(HEADERS)
	@echo "Object files: $(OBJECTS)"

ifeq ($(RASPI_MODEL), 2)
	@echo "Building kernel image for Raspberry Pi $(RASPI_MODEL)"
	$(CC) -T linker.ld -o $(ELF_NAME) $(LDFLAGS) $(OBJECTS)
	$(OBJCOPY) $(ELF_NAME) -O binary $(RASPI_IMG)
else
	@echo "Building kernel image for VM"
	$(CC) -T linker.ld -o $(IMG_NAME) $(LDFLAGS) $(OBJECTS)

endif



$(OBJ_DIR)/%.o: $(KER_SRC)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KER_SRC) -I$(KER_HEAD) -c $< -o $@ $(CSRCFLAGS)

$(OBJ_DIR)/%.o: $(KER_SRC)/%.S
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KER_SRC) -c $< -o $@

$(OBJ_DIR)/%.o: $(COMMON_SRC)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KER_SRC) -I$(KER_HEAD) -c $< -o $@ $(CSRCFLAGS)

clean:
	rm -rf $(OBJ_DIR)
	rm *.img *.elf

run: build
	qemu-system-arm -m 256 -M raspi2 -serial stdio -kernel kernel.img
