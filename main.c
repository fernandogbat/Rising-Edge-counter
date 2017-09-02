#include "TM4C123.h"                    // Device header
#include<stdint.h>
void Timer3A_countCapture_init(void);
int Timer3A_countCapture(void);
uint32_t count;
int main()
{
	 Timer3A_countCapture_init();
	 while(1){
	 count=0;
	 count = Timer3A_countCapture();
	 }
}
void Timer3A_countCapture_init(void)
{
    SYSCTL->RCGCTIMER |= 8;     /* enable clock to Timer Block 3 */
    SYSCTL->RCGCGPIO |= 2;      /* enable clock to PORTB */

    GPIOB->DIR &= ~0x04;        /* make PB2 an input pin */
    GPIOB->DEN |= 0x04;         /* make PB2 a digital pin */
    GPIOB->AFSEL |= 0x04;       /* enable alternate function on PB2 */
    GPIOB->PCTL &= ~0x00000F00;  /* configure PB2 as T3CCP0 pin */
    GPIOB->PCTL |= 0x00000700;
    
    TIMER3->CTL &= ~1;          /* disable TIMER3A during setup */
    TIMER3->CFG = 4;            /* configure as 16-bit timer mode */
    TIMER3->TAMR = 0x13;        /* up-count, edge-count, capture mode */
    TIMER3->TAMATCHR = 0xFFFF;  /* set the count limit */
    TIMER3->TAPMR = 0xFF;	      /* to 0xFFFFFF with prescaler */
    TIMER3->CTL &= ~0xC;        /* capture the rising edge */
    TIMER3->CTL |= 1;           /* enable timer3A */
}

int Timer3A_countCapture(void)
{
    return TIMER3->TAR;
}