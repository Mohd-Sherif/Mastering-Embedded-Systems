#include "uart.h"

#define UART0DR (*((volatile unsigned int *)(0x101f1000)))

void UART_vSendString(unsigned char *str){
	while (*str != '\0'){
		UART0DR = *str;
		str++;
	}
}