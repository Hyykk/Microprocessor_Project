#ifndef ADC_H_
#define ADC_H_

void ADC_Init(){
	ADCSRA |= (1 << ADEN);  // Enable ADC
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);	// prescaler for adc (prescaler = 128 -> range : 0~1023)
}

unsigned short ADC_read(unsigned short channel){
	// ADC channel selecting
	ADMUX = (ADMUX & 0xF0) | (channel & 0x07);
	
	// Start converting
	ADCSRA |= (1 << ADSC);
	
	// Waiting for finish converting
	while (ADCSRA & (1 << ADSC));
	
	// return adcvalue
	return ADC;
}

#endif /* ADC_H_ */