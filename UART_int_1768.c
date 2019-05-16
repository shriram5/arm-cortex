#include <lpc17xx.h>

void uart_init(void)
{
			LPC_PINCON->PINSEL0 |=(1<<4)|(1<<6);

			LPC_UART0->LCR |=(1<<0)|(1<<1)|(1<<7);
			LPC_UART0->DLL=163;
			LPC_UART0->DLM=0x00;
		
			LPC_UART0->LCR &=~(1<<7);  //DLAB clear
			//LPC_UART0->TER |=(1<<7);    //transmission complete not required here in interrupt
}
/*void UART0_IRQ_HANDLER()
{			
			//while(!(LPC_UART0->LSR & (1<<5)));
			//LPC_UART0->THR=LPC_UART0->RBR;
}*/
void UART0_IRQ_HANDLER(unsigned char *PTR)
{
	while(!(LPC_UART0->LSR & (1<<5)));
	LPC_UART0->THR=LPC_UART0->RBR;
			while(*PTR)
		{
					write(*PTR);
					PTR++;
		}
}
unsigned char read(void)
{
			while(!(LPC_UART0->LSR & (1<<0)));
			return LPC_UART0->RBR;
}

void write(unsigned char C)
{
			while(!(LPC_UART0->LSR & (1<<5)));
			LPC_UART0->THR=C;
}

/*void write_text()
{
	unsigned char PTR[10]="kuch bhi";
		while(*PTR)
		{
					write(*PTR);
					PTR++;
		}
}*/

int main(void)
{
			uart_init();
			
			unsigned char PTR[30]="hi hello kat le /r /n";
			
			UART0_IRQ_HANDLER(PTR);
			
			while(1)
			{
				write(read());
			}
			LPC_UART0->TER |=(1<<7);
			LPC_UART0->IER |=(1<<0);
			NVIC_EnableIRQ(UART0_IRQn);
}
