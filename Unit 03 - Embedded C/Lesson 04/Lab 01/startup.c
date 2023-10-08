/**
 * learn-in-depth:<Mohamed Sherif>
 */

#include <stdint.h>

#define STACK_START_SP 0x20001000

extern int main(void);
extern unsigned int _E_text;
extern unsigned int _S_data;
extern unsigned int _E_data;
extern unsigned int _S_bss;
extern unsigned int _E_bss;

static unsigned long stack_top[256]; // 256*4 = 1024B

void Rest_handler(void){
	/* copy .data from ROM to RAM */
	unsigned int data_size = (unsigned char *) &_E_data - (unsigned char *) &_S_data;
	unsigned char *srcPtr = (unsigned char *) &_E_text;
	unsigned char *dstPtr = (unsigned char *) &_S_data;
	for (int i = 0; i < data_size; i++)
		*((unsigned char *)dstPtr++) = *((unsigned char *)srcPtr++);
	
	/* initialize .bss with zero*/
	unsigned int bss_size = (unsigned char *) &_E_bss - (unsigned char *) &_S_bss;
	dstPtr = (unsigned char *) &_S_bss;
	for (int i = 0; i < bss_size; i++)
		*((unsigned char *)dstPtr++) = (unsigned char) 0;
	
	/* jump to main */
	main();
}

void Default_handler(void){
	Rest_handler();
}

void NMI_handler(void) __attribute__((weak, alias("Default_handler")));
void H_fault_handler(void) __attribute__((weak, alias("Default_handler")));
/* ... */

void (* const gPtrFnVectors[]) () __attribute__((section(".vectors"))) = {
	(void (*)()) ((unsigned long)stack_top + sizeof(stack_top)),
	&Rest_handler,
	&NMI_handler,
	&H_fault_handler
	/* ... */
};