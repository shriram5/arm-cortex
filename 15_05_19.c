#include <stdio.h>
#include <lpc17xx.h>
#include "lcd.h"

void ADC_init()
{
	LPC_PINCON->PINSEL1 |=(1<<18);
	LPC_SC->PCONP |=(1<<12);
	LPC_ADC->ADCR |=(1<<2)|(1<<16)|(1<<21);
	
}
void UART_init()
{
	LPC_PINCON->PINSEL0 |=(1<<4)|(1<<6);
	LPC_SC->PCONP |=(1<<3);
	LPC_UART0->LCR |=(1<<0)|(1<<1)|(1<<7);
	LPC_UART0->DLL =0xA3;
	LPC_UART0->DLM =0x00;
	
	LPC_UART0->TER =(1<<7);
	LPC_UART0->LCR &=~(1<<7);
}
 /*unsigned char receive()
 {
	 while(!(LPC_UART0->LSR & (1<<0)));
	 return LPC_UART0->RBR;
 }*/
  void transmit(unsigned char ch)
	{
		if(ch == '/n')
		{
		while(!(LPC_UART0->LSR & (1<<5)));
		LPC_UART0->THR = 0x0d;
		}
		while(!(LPC_UART0->LSR & (1<<5)));
		LPC_UART0->THR = ch;
	}
	
	void text(unsigned char ch[])
	{
		while(*ch++)
		{
			transmit(*ch);
		}
		
	}
	
	int main()
	{
		float volt;
		int result;
		unsigned char adc[10]="===ADC===";
		
		unsigned char arr[10];
		ADC_init();
		init_lcd();
		
		
	//	UART_init();
		while(1)
		{	
			send_cmd(0x80);  			//print form 1st line
			user_string(adc);
			while(!(LPC_ADC->ADSTAT & (1<<2)));
			result= LPC_ADC->ADDR2 & 0x0000FFF0;
			result= result>>4;
			volt = (result*3.3)/4096;
			sprintf(arr,"ADC=%0.2f",volt);		
			
			
			send_cmd(0xc0);   //print form 2nd line
			user_string(arr);

			//text(arr);
			
		for(int i=0;i<20;i++)
		{
			transmit(arr[i]);
		}
		for(int i=0;i<1000000;i++)
		for(int j=0;j<100000;j++);
		}
}
	
	