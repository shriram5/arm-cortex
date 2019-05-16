#include <lpc17xx.h>


void uart_init(void)
{
			LPC_PINCON->PINSEL0 |=(1<<4)|(1<<6);
			//LPC_SC->PCLKSEL0=0x00000000;
			
			LPC_UART0->LCR |=(1<<0)|(1<<1)|(1<<7);
			LPC_UART0->DLL=163;
			LPC_UART0->DLM=0x00;
		//	LPC_UART0->FDR=0x00;
	
			LPC_UART0->LCR &=~(1<<7);  //DLAB clear
			LPC_UART0->TER |=(1<<7);    //transmission enable
}
unsigned char read(void)
{
			while(!(LPC_UART0->LSR & (1<<0)));
			return LPC_UART0->RBR;
}

void write(unsigned char data)
{
			while(!(LPC_UART0->LSR & (1<<5)));
			LPC_UART0->THR=data;
}

void write_text(unsigned char PTR[])
{
		//unsigned char *msg;
		while(*PTR)
		{
					write(*PTR);
					PTR++;
		}
}
int main(void)
{
			uart_init();
			unsigned char PTR[30]="hi hello kat le /r /n";
			
			write_text(PTR);
			
			while(1)
			{
				write(read());
			}
			
}
