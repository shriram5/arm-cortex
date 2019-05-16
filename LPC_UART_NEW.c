#include <LPC17xx.h>
#include <stdio.h>
#include "lcd1768.h"

void ADC_init()																													//for ADC at channel 2																																			//since pot is connected at channel 2
{
	LPC_PINCON->PINSEL1 |=(1<<18);														//enable ADC 2
														
	LPC_ADC->ADCR |=((1<<2) | (1<<8) | (1<<16) | (1<<21));													//enable conversion of ADC 2
	//LPC_SC->PCLKSEL0 |=((1<<25) | (1<<24));			//peripheral clock
	
}

void UART0_init()
{
																									//enable power to UART1
	//LPC_SC->PCLKSEL0 |=((1<<7) | (1<<6));																	//peripheral clock 
																																					//100MHz/8 = 12.5MHz
																																					//12.5MHz/(9600*16)
	LPC_PINCON->PINSEL0 |=(1<<4)  | (1<<6);		
	LPC_UART0->LCR =0x83;
	//LPC_UART0->LCR |=(1<<7);
	LPC_UART0->DLL =162;
	LPC_UART0->DLM =0x00;
	
	LPC_UART0->TER |=(1<<7);
	LPC_UART0->LCR =0x03;
}

/*unsigned char UART0_Rx()
{
	while(!(LPC_UART0->LSR & (1<<0)));
	return LPC_UART0->RBR;
}
*/
void UART0_Tx(unsigned char ch)
{
	if (ch == '\n')
		{
				while(!(LPC_UART0->LSR & 0x20));                            //checking for transmittting buffer to be empty 
				LPC_UART0->THR =0x0d;																				//Carriage return	
		}
	while(!(LPC_UART0->LSR & (1<<5)));
	LPC_UART0->THR=ch;
}
/*void write_text(unsigned char ch[])
{
	while(*ch++)
	{
		UART0_Tx(*ch);
	}
}*/

int main()
{
	unsigned char arr[10];
	int result;
	LPC_SC->PCONP |= ((1<<12) | (1<<3));	
	ADC_init();
	UART0_init();
	//char *ptr = "**ADC**";
//	LPC_SC->PCLKSEL0 = 0x00;
	//send_cmd(0x40);
	//user_string(ptr);
	while(1)
	{
												//++++++++++++++++++++++++++++++++++++++++++
	while(!(LPC_ADC->ADSTAT & (1<<2)));
	//result= LPC_ADC->ADDR2 ;
	result= LPC_ADC->ADDR2 & 0x0000FFF0;
	result=result >> 4;

	float volt= (result*3.3)/4096;
		sprintf(arr,"ADC value:%d",volt); //storing value of volt in a buffer "arr"
		//send_cmd(0xc0);
	  //user_string(arr);																	//++++++++++++++++++++++++++++++++++++++++++
	
	
	//for(int i=0; i<20; i++)
		//{		write_text(*arr);
				//UART0_Tx(UART0_Rx());
		//}
		for(int i=0; i<20; i++)
		{		//write_text(*arr);
				UART0_Tx(arr[i]);
		}
	}
for(int i=0;i<5000;i++)
	for(int j=0;j<1000;j++);
}


