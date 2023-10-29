

CC=avr-gcc

LD=avr-ld

#ARCH=avr5
ARCH=atmega328p

# ffreestanding - turn off builtin C functions like _exit and main
#CCFLAGS=-DF_CPU=16000000UL -c -mmcu=$(ARCH) -std=gnu11 -ffreestanding -Wall -Os

CCFLAGS=-DF_CPU=16000000UL -c -mmcu=$(ARCH) -std=gnu11 -Wall -Os

LDFLAGS=-mmcu=$(ARCH) --specs=/home/andrii/repos/toolchain/avr8-gnu-toolchain-linux_x86_64/lib/gcc/avr/7.3.0/device-specs/specs-atmega328p -T atmega328p_linker.ld -Wl,-Map=final.map

# nostdlib - do not link to standard C library
# -Wl - pass in a linker argument
# -Map - linker generates a Map file 
#LDFLAGS=-mmcu=$(ARCH) -nostdlib -T atmega328p_linker.ld -Wl,-Map=final.map
#LDFLAGS=-mmcu=$(ARCH) -nostdlib -T atmega328p_linker.ld -Wl,-Map=final.map

main.o:main.c
	$(CC) $(CCFLAGS) $^ -o $@


atmega328p_startup.o:atmega328p_startup.c
	$(CC) $(CCFLAGS) $^ -o $@



final.elf:main.o atmega328p_startup.o
	$(CC) $(LDFLAGS) $^ -o $@




dissass:
	avr-objdump -D ./final.elf > diss_elf.txt
	avr-objdump -t final.elf > syms_table.txt



clean:
	rm -rf *.o *.elf *.hex *.bin *.map *.txt




upload:
	avr-objcopy -O ihex -R .eeprom final.elf final.hex
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:final.hex



toolchain_test:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o test.o test.c
	avr-gcc -mmcu=atmega328p test.o -o test.elf
	avr-objcopy -O ihex -R .eeprom test.elf test.hex

test_upload:
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:test.hex