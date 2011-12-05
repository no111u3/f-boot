# f-boot

# cross compile
CROSS_COMPILE = arm-softfloat-linux-gnueabi-
# compilator aliases
AS = $(CROSS_COMPILE)gcc -c
LD = $(CROSS_COMPILE)ld
CC = $(CROSS_COMPILE)gcc
OC = $(CROSS_COMPILE)objcopy
OD = $(CROSS_COMPILE)objdump
# other tools aliases
RM = rm -f

# basic vars
GCCLIBDIR := $(shell dirname `$(CC) -print-libgcc-file-name`)
ENTRY = start_entry
OFFSET = 0
OUT = f-boot
ASRCS = $(wildcard *.S)
AOBJS = $(ASRCS:.S=.o)
CSRCS = $(wildcard *.c)
COBJS = $(CSRCS:.c=.o)
OBJS = $(AOBJS) $(COBJS) 

# flags
## architecture flags
ARCH_FLAGS = -march=armv4t -mtune=arm920t -mabi=aapcs-linux
## assembler flags
AFLAGS = $(ARCH_FLAGS) -I../include/
## compiler flags
CFLAGS = $(ARCH_FLAGS) -Wall -std=c99 -pipe -Os -I../include/
## linker flags
LFLAGS = -e $(ENTRY) -Ttext $(OFFSET) -Os -L$(GCCLIBDIR) -lgcc

# taget
all: $(OUT).bin

# object dump
$(OUT).bin: $(OUT)
	@ echo '  OCOPY	' $@
	@ $(OC) -j .text -j .rodata -O binary $< $@

# linked object
$(OUT): $(OBJS)
	@ echo '  LD	' $(OUT)
	@ $(LD) -o $(OUT) $(OBJS) $(LFLAGS)
# compiling assembler sources
.S.o:
	@ echo "  AS	" $@
	@ $(AS) $(AFLAGS) -o $@ $<
# compiling C sources
.c.o:
	@ echo "  CC	" $@
	@ $(CC) -c $(CFLAGS) -o $@ $<
# assembler listing
asm:
	@ echo '  ODUMP	' $(OUT)
	@ $(OD) -D $(OUT)
# assemble data listing
asmb:
	@ echo '  ODUMP	' $(OUT)
	@ $(OD) -b binary -m armv4t -D $(OUT).bin

# cleaning binary files
clean:
	@ echo '  RM	' $(OUT) $(OUT).bin $(OBJS)
	@ $(RM) $(OUT) $(OUT).bin $(OBJS)