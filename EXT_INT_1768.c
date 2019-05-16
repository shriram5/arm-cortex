#include <lpc17xx.h>

void EXT_init()
{
			LPC_PINCON->PINSEL4 |=(1<<24);
			//LPC_SC->EXTINT |=(1<<2);
			LPC_SC->EXTMODE &=~(1<<2);
			LPC_SC->EXTPOLAR &=~(1<<2);
}
void led_off()
{
			LPC_GPIO2->FIOSET1 |=(1<<1);
		
}
void led_on()
{
			LPC_GPIO2->FIOCLR1 |=(1<<1);
			
}
 void EINT2_IRQHandler()__irq
 {
			static int c=0;
			if(c==0)
			{	
					LPC_GPIO2->FIOCLR1 |=(1<<3);
					
					led_off();
					c=1;
			}		
			else 
			{
					LPC_GPIO2->FIOSET1 |=(1<<3);
					
					led_on();
					c=0;
			}
			LPC_SC->EXTINT |=(1<<2);
}
int main(void)
{
	
			LPC_GPIO2->FIODIR1 |=(1<<1) |(1<<3);
			EXT_init();
			
			NVIC_EnableIRQ(EINT2_IRQn);
			while(1){}
}	
