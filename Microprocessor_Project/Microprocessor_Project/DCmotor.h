#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#define DClow 175
#define DChigh 255

void DC_Init() {
	// Fast PWM Mode
	TCCR0 |= (1 << WGM00) | (1 << WGM01);
	// non-inversion
	TCCR0 |= (1 << COM01);
	// prescaler 64로 설정
	TCCR0 |= (1 << CS00) | (1 << CS01);
	
	DDRA |= (1 << PA0) | (1 << PA1);
	
	PORTA |= (1 << PA0);
	PORTA &= ~(1 << PA1);
}

// Moving DC
void DC_speed(unsigned short speed){
	OCR0 = speed;
}

#endif /* DCMOTOR_H_ */