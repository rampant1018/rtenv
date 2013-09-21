#include "utils.h"
#include "stm32f10x.h"
#include "RTOSConfig.h"

int strcmp(const char *a, const char *b) __attribute__ ((naked));
int strcmp(const char *a, const char *b)
{
	asm(
        "strcmp_lop:                \n"
        "   ldrb    r2, [r0],#1     \n"
        "   ldrb    r3, [r1],#1     \n"
        "   cmp     r2, #1          \n"
        "   it      hi              \n"
        "   cmphi   r2, r3          \n"
        "   beq     strcmp_lop      \n"
		"	sub     r0, r2, r3  	\n"
        "   bx      lr              \n"
		:::
	);
}

size_t strlen(const char *s) __attribute__ ((naked));
size_t strlen(const char *s)
{
	asm(
		"	sub  r3, r0, #1			\n"
        "strlen_loop:               \n"
		"	ldrb r2, [r3, #1]!		\n"
		"	cmp  r2, #0				\n"
        "   bne  strlen_loop        \n"
		"	sub  r0, r3, r0			\n"
		"	bx   lr					\n"
		:::
	);
}

void puts(char *s)
{
	while (*s) {
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
			/* wait */ ;
		USART_SendData(USART2, *s);
		s++;
	}
}

void int2str(int input, char *output) ;
void printf(char *output);

int strncmp(char *val1, char *val2, int length)
{
    	int i;

    	for(i = 0; i < length; i++) {
    	    	if(val1[i] != val2[i]) {
    	    	    	return val1[i] - val2[i];
	    	}
	}

	return 0;
}

void printf(char *output)
{
	int fdout;    

	fdout = mq_open("/tmp/mqueue/out", 0);

	write(fdout, output, strlen(output) + 1);
}

void int2str(int input, char *output) 
{
	char tmp[16];
	int num_len = 0, i;

	if(input == 0) {
	    output[0] = '0';
	    output[1] = '\0';
	    return;
	}

	while(input > 0) {
		tmp[num_len++] = '0' + (input % 10);
		input /= 10;
	}

	for(i = 0; i < num_len; i++) {
	    output[i] = tmp[num_len - i - 1];
	}
	output[num_len] = '\0';
}
