
/* CONVERT the VALUES and DISPLAY it on UART and LCD in VOLATAGE or millivolt 
		
		PRN=0063 and 0064
*/


#include"lpc17xx.h"
#include<stdio.h>
#include"LCD_1768.h"
#define CR 0x0D

//Initilization of ADC
void adc_init()
{

		LPC_PINCON->PINSEL1 = (1<<18);																		//p0.25 connected to pot
		LPC_ADC->ADCR |= (1<<2)| (1<<8) |(1<<16) | (1<<21)  ;							//burst mode on , pdn bit set, 
	                                                                	//cclk divided by this value+1 to obtain 13MHZ or less than that
}

//Initilization of UART
void uart_init()
{
		LPC_PINCON->PINSEL0 |= (1<<1) | (1<<3);     										//p0.0 p0.1, TXD3 RXD3 set
		LPC_SC->PCONP |=  (1<<25);                  										//UART3 enable
	
		LPC_UART3->LCR = 0x83;																					//dlab=1 , word len=8bit
		LPC_UART3->DLL = 162;                       										//dll=162 dlm=0 for baudrate=9600
		LPC_UART3->TER = (1<<7);                    										//transmit enable
		LPC_UART3->LCR = 0x03;                      										//dlab=0
}

//Transmit data
void Tx(char data)																									//function for transmit the data 
{
		if (data == '\n')
		{
				while(!(LPC_UART3->LSR & 0x20));                            //checking for transmittting buffer to be empty 
				LPC_UART3->THR = CR;																				//Carriage return	
		}
		while(!(LPC_UART3->LSR & 0x20));                                //checking for transmittting buffer to be empty 
		LPC_UART3->THR = data;																					//transmit data
}

//------------------------------------------------------------------------------------------
//                              MAIN FUNCTION
//------------------------------------------------------------------------------------------
int main(void)																	
{
	  LPC_SC->PCONP |=  (1<<25)|(1<<12);  														//power up the ADC by setting bit 12 and the UART3 by setting bit 25 
		init_lcd();                                                     //calling LCD initialization
		adc_init();                                                     //calling ADC initialization
	  uart_init();                                                    //calling UART initialization				       	
	  
																																		//UART3 enable and adc enable
	  LPC_SC->PCLKSEL1 = 0x00;	
    char *ptr = "**ADC**";	
		float voltage;
	  int result;
    char arr[20];
																														//pclk = 25MHz
	
	  send_cmd(0x40);
	  user_string(ptr);
		while(1)
		{
				while(*ptr)
				{
						Tx(*ptr++);
				}
		
				while(!(LPC_ADC->ADSTAT & 0x00000004));
				result = LPC_ADC->ADDR2 & 0x0000FFF0;
				result = result>>4;
				voltage=(result*3.3)/4096;
				sprintf(arr, "ADC:%.2f",voltage);
				send_cmd(0xc0);
				user_string(arr);
		
				for(int i=0;i<20;i++)
				{
						Tx(arr[i]); 
  		
				}
		
		}
		
		//DELAY
		for(int i=0;i<5000;i++)
			for(int j=0;j<1000;j++);

}


	
	
	
	
	
	
	
	
	