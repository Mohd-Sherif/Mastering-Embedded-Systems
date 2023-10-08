# learn-in-depth:<Mohamed Sherif> 

CC=arm-none-eabi-
CFLAGS=-mcpu=cortex-m3 -gdwarf-2 -c
INCS=-I .
LIBS=
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
As=$(wildcard *.s)
AsOBJ=$(As:.s=.o)
ProjectName=learn-in-depth_cortexM3

all: $(ProjectName).bin
	@echo "=====Build done====="

%.o: %.s
	$(CC)as.exe $(CFLAGS) $< -o $@
	
%.o: %.c
	$(CC)gcc.exe $(CFLAGS) $(INCS) $< -o $@

$(ProjectName).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(AsOBJ) -o $@ -Map=map_file.map

$(ProjectName).bin: $(ProjectName).elf
	$(CC)objcopy.exe -O binary $< $@

clean:
	rm -f *.elf *.bin
	@echo "======Clean====="

clean_all:
	rm -f *.o *.elf *.bin *.map
	@echo "=====Everything is clean====="