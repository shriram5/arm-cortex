#include <lpc17xx.h>

void timer_init(void)
{

		LPC_SC->PCLKSEL0 |= (1<<2);
		LPC_TIM0->CTCR = 0x00;
		LPC_TIM0->PR = 0x186A0;
		LPC_TIM0->TCR =(1<<1);
		LPC_TIM0->MCR |=(1<<1);
}

void reset_on_match(unsigned int ms)
{
     LPC_TIM0->MCR |=(1<<1);
		 LPC_TIM0->MR0 = ms;
	   LPC_TIM0->TCR = (1<<0);
	   while(!(LPC_TIM0->TC & 1000000));
}

void stop_on_match(unsigned int ms)
{
		 LPC_TIM0->MCR |=(1<<0);
		 LPC_TIM0->MR0 = ms;
		 LPC_TIM0->TCR |=(1<<1);
		 LPC_TIM0->TCR |=(1<<0); 
		 while(!(LPC_TIM0->TC & 1000000));
}

int main(void)
{
	
	//LPC_PINCON->PINSEL4 |= (1<<23) | (1<<22) | (1<<19) | (1<<18);
		//LPC_GPIO2->FIODIR= 0xFF;
	   LPC_GPIO2->FIODIR1 |= (1<<3)|(1<<1);                      //bit 3 for buzz and bit 1 for led set only that pins otherwise all pins acts as output
		 timer_init();
	   while(1)
	   {
		//LPC_GPIO2->FIOSET |= (1<<19) | (1<<20);
	        LPC_GPIO2->FIOSET1  |= /*(1<<3)|*/ (1<<1);   //bit 3 for buzz and bit 1 for led
		
		
		      reset_on_match(1000000);
		//LPC_GPIO2->FIOCLR0 |= (1<<19) | (1<<20);
		      LPC_GPIO2->FIOCLR1 |= /*(1<<3)|*/ (1<<1);
		      reset_on_match(1000000);
		
		//stop_on_match(1000);
	
     }	
	
}


