#include "uart.h"

unsigned char stringBuffer[100] = "learn in depth:<Mohamed Sherif>";

void main(void){
	UART_vSendString(stringBuffer);
}