#include <lpc17xx.h>

void delay(int time)
{			
			unsigned int i,j;
			for(i=0;i<10000;i++)
					for(j=0;j<time;j++);
}
void spi_init()
{
			LPC_PINCON->PINSEL0 |=(1<<31) | (1<<30);
			LPC_PINCON->PINSEL1 |=/*(1<<3)|*/(1<<5)|(1<<4);
			//LPC_GPIO0->FIOSET2 |=(1<<0);
			//LPC_SC->PCLKSEL0=0x00;
			LPC_SPI->SPCR=0x00;
			LPC_SPI->SPCR |=(1<<5);
			LPC_SPI->SPCCR =0x10;			
}

void SPI_IRQHandler (void)__irq
{		
			LPC_GPIO0->FIOSET2 |=(1<<0);
			LPC_SPI->SPDR=0xFF;
			while(!(LPC_SPI->SPSR & (1<<7)));
			LPC_GPIO0->FIOCLR2 |=(1<<0);
			delay(100);
			
			LPC_GPIO0->FIOSET2 |=(1<<0);
			LPC_SPI->SPDR=0x00;
			while(!(LPC_SPI->SPSR & (1<<7)));
			LPC_GPIO0->FIOCLR2 |=(1<<0);
			delay(100);
}
int main(void)
{		
			spi_init();
			LPC_GPIO0->FIODIR2 =0xFF;
			LPC_SPI->SPINT |=(1<<0);
			
			NVIC_EnableIRQ(SPI_IRQn);
}



