

CC=avr-gcc

LD=avr-ld

ARCH=avr5


# ffreestanding - turn off builtin C functions like _exit and main
CCFLAGS=-c -mmcu=$(ARCH) -std=gnu11 -ffreestanding -Wall -O0

#LDFLAGS=-mmcu=$(ARCH) --specs=/home/andrii/repos/toolchain/avr8-gnu-toolchain-linux_x86_64/lib/gcc/avr/7.3.0/device-specs/specs-atmega328p -T avr_linker.ld -Wl,-Map=final.map

# nostdlib - do not link to standard C library
# -Wl - pass in a linker argument
# -Map - linker generates a Map file 
LDFLAGS=-mmcu=$(ARCH) -nostdlib -T avr_linker.ld -Wl,-Map=final.map


main.o:main.c
	$(CC) $(CCFLAGS) $^ -o $@


avr_startup.o:avr_startup.c
	$(CC) $(CCFLAGS) $^ -o $@



final.elf:main.o avr_startup.o
	$(CC) $(LDFLAGS) $^ -o $@




dissass:
	avr-objdump -D ./final.elf >> diss.elf



clean:
	rm -rf *.o *.elf *.map



