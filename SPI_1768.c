#include <lpc17xx.h>

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

void spi_write(unsigned int data)
{	
			LPC_GPIO0->FIOSET2 |=(1<<0);
			LPC_SPI->SPDR=data;
			while(!(LPC_SPI->SPSR & (1<<7)));
			LPC_GPIO0->FIOCLR2 |=(1<<0);			
}
void delay(int time)
{			
			unsigned int i,j;
			for(i=0;i<10000;i++)
					for(j=0;j<time;j++);
}
int main(void)
{
			spi_init();
			
			LPC_GPIO0->FIODIR2 =0xFF;
			while(1)
			{
						spi_write(0xFF);
						delay(100);
						spi_write(0x00);
						delay(100);
			}
}
