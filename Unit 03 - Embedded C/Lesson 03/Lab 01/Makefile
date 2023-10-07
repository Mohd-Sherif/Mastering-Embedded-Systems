# learn-in-depth:<Mohamed Sherif>

learn-in-depth.bin: app.c uart.c startup.s
	arm-none-eabi-gcc.exe -mcpu=arm926ej-s -g -c -I . app.c -o app.o
	arm-none-eabi-gcc.exe -mcpu=arm926ej-s -g -c -I . uart.c -o uart.o
	arm-none-eabi-as.exe -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-ld.exe -T linker_script.ld startup.o app.o uart.o -o learn-indepth.elf -Map=map_file.map
	arm-none-eabi-objcopy.exe -O binary learn-indepth.elf learn-indepth.bin
	@echo "=======Build done======="

clean:
	rm -f *.elf *.bin

clean_all:
	rm -f *.o *.elf *.bin *.map