#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

// Trig : PC4
// Echo : PD3

#define Trigger_ON      PORTC |= (1 << PC4)   // Trig PIN ON
#define Trigger_OFF     PORTC &= ~(1 << PC4)  // Trig PIN OFF

// Get distance
double getEcho(){
	TCCR2 |= (1 << CS22) | (1 << CS20);
	
	Trigger_ON;
	_delay_us(10);     // Waiting 10us
	Trigger_OFF;
	
	while(!(PIND & (1<<PIND3)))     // When Echo is HIGH
	;
	TCNT2 = 0;     // Timer2 reset

	while(PIND & (1<<PIND3))     // When Echo is LOW
	;
	TCCR2 &= ~((1 << CS22) | (1 << CS20));     // Timer2 stop

	return TCNT2/58.8 * 100;     // return distance(cm)
}

// Settings for Ultrasonic Sensor
void Ultrasonic_Init(){
	DDRD &= ~(1 << DDD3);    // PD3 input Echo
}
#endif /* ULTRASONIC_H_ */