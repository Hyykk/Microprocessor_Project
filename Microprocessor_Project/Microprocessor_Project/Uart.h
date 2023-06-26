#ifndef UART_H_
#define UART_H_

#include "Include.h"

// Receive
void USART0_TX_vect(unsigned char data){
	while(!(UCSR0A & (1<<UDRE0)));	// UDRE = 1 -> buffer empty -> ready to write
	
	UDR0 = data;
}

// Send
unsigned char USART0_RX_vect(void){
	while(!(UCSR0A & (1<<RXC0)));
	
	return UDR0;
}

// Settings for USART
void USART_Init(void){
	//UCSR0A = ;	// flag 검사
	UCSR0B = 0b00011000;	// 송수신 활성화, 인터럽트 활성화
	//(1<<RXEN0)||(1<<TXEN0);
	
	// 데이터 비트 수, 동기/비동기. stop bit 수
	UCSR0C = 0b00000110;	// 비동기, no parity, 1 stop bit
	
	// Baud Rate
	UBRR0H = 0x00;	// UBRR0H = (unsigned char)(103>>8);
	UBRR0L = 103;	// UBRR0L = (unsigned char) 103;
}

// Convert int to string
void USART_Transnum(int num){
	if (num <0)
	{
		USART0_TX_vect(45);            // if number < 0 print '-' and abs(num)
		num = -num;
	}
	USART0_TX_vect((num/10000)+48);            // 10000
	USART0_TX_vect(((num%10000)/1000)+48);      // 1000
	USART0_TX_vect(((num%1000)/100)+48);      // 100
	USART0_TX_vect(((num%100)/10)+48);         // 10
	USART0_TX_vect(((num%10)+48));            // 1
	USART0_TX_vect(13);         //엔터
}

#endif /* UART_H_ */