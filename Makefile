GCCPATH = /opt/gcc-arm/bin

CC 			= $(GCCPATH)/aarch64-none-elf-gcc
LD 			= $(GCCPATH)/aarch64-none-elf-ld
OBJCOPY 	= $(GCCPATH)/aarch64-none-elf-objcopy
GCCFLAGS 	= -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles

OUTDIR = ./out/bin

HFILES = $(wildcard *.h include/*.h)
CFILES = $(wildcard *.c src/*.c)
_OFILES = $(CFILES:.c=.o)
OFILES = $(_OFILES:src/%=out/%)

all: clean kernel8.img

out/boot.o: src/boot.S
	@echo "Building $@"
	@mkdir -p $(@D)
	@$(CC) -c $< -o $@ $(GCCLFAGS)

out/%.o: src/%.c $(HFILES)
	@echo "Building $@"
	@mkdir -p $(@D)
	@$(CC) -Iinclude -c $< -o $@ $(GCCLFAGS)

kernel8.img: out/boot.o $(OFILES)
	@echo "Linking kernel"
	@mkdir -p bin
	@$(LD) -nostdlib out/boot.o $(OFILES) -T link.ld -o out/kernel8.elf
	@$(OBJCOPY) -O binary out/kernel8.elf bin/kernel8.img
	@echo "Done!"

clean:
	@/bin/rm -rf out/ > /dev/null 2> /dev/null || true