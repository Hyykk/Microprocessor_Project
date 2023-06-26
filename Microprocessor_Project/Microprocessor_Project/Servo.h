#ifndef SERVO_H_
#define SERVO_H_

// Moving Servo
unsigned int set_servo(double angle){
	double width;
	double duty;
	
	width = (angle/90)+0.5;
	
	duty = (width/20.0)*100;
	
	OCR1A = (int)(duty/100 *ICR1);
	return OCR1A;
}

// Settings for Servo
void Servo_Init(){
	TCCR1A = 0x82;
	TCCR1B = 0x1b;
	ICR1 = 4999;     //TOP
	TIMSK = (1 << TOIE1);
}

// Test Servo
void test_servo(){
	set_servo(0);
	_delay_ms(1000);
	set_servo(180);
	_delay_ms(1000);
	set_servo(90);
	_delay_ms(1000);
}
#endif /* SERVO_H_ */

// PB5핀 사용 중