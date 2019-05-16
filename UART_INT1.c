#include<LPC17XX.H>

	
void delay()
{
	for(int i=0;i<1000;i++)
	{
		for(int j=0;j<1000;j++)
		{
			;
		}
	}
		
	
}
void led_on()
{
	LPC_GPIO2->FIOCLR1=0X02;//LED ON
}

void led_off()
{
	LPC_GPIO2->FIOSET1=0X02;//LED OFF
}



int main()
{ 
	LPC_PINCON->PINSEL4=~(0x00CC0000);
	LPC_GPIO2->FIODIR1=0X02;//SET DIRECTION TO LED AS OUTPUT 
	LPC_GPIO2->FIOSET1=0X02;//LED OFF
	LPC_SC->PCLKSEL0 |= (0<<7)|(0<<6);//25 MHZ
	LPC_PINCON->PINSEL0 |=(1<<4)|(1<<6);//SELECT TXD0,RXD0;
	LPC_UART0->LCR |=(1<<0)|(1<<1)|(1<<7);//DLAB=1,8 BIT CHAR LENGTH,STOP BIT
	LPC_UART0->DLL =0XA2;
	LPC_UART0->DLM =0X00;
	LPC_UART0->LCR =(1<<0)|(1<<1)|(0<<7);//DLAB=0,8 BIT CHAR LENGTH,STOP BIT
	LPC_UART0->TER |=(1<<7);//TRANSMISSION ENABLE
	
  NVIC_EnableIRQ(UART0_IRQn);
	LPC_UART0->IER |=(1<<0);//INTERRUPT ENABLE
	
 	while(1)
	{
	  //delay();
	}
}
		
void UART0_IRQHandler(void)
{
	led_on();
	 delay();
		while(!(LPC_UART0->LSR &0X20));//CHECK THRE
   LPC_UART0->THR=LPC_UART0->RBR;
	 
	 delay();
	 led_off();
	 
}