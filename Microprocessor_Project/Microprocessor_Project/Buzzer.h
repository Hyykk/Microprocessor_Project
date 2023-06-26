#ifndef BUZZER_H_
#define BUZZER_H_

// Turn on the Buzzer(frequency, magnitude)
void BuzzerOn(double hz, int magnitude){
	for(int i = 0; i < magnitude; i ++){
		PORTC |= (1 << PC3);
		_delay_ms((1000/hz)/2);
		PORTC &= ~(1 << PC3);
		_delay_ms((1000/hz)/2);
	}
}

// Turn off the buzzer
void BuzzerOff(){
	PORTC &= ~(1 << PC3);
}

#endif /* BUZZER_H_ */