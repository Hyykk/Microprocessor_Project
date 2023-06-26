#include "Include.h"
#include "Uart.h"
#include "Adc.h"
#include "Servo.h"
#include "Led.h"
#include "Convert.h"
#include "DCmotor.h"
#include "Ultrasonic.h"
#include "Buzzer.h"
#include "MAF.h"
#include "IIR.h"
#include "FIR.h"
#include "Kalman.h"

double filtered_pre;

int main(void){
	
	// Settings
	USART_Init();
	ADC_Init();
	LED_Init();
	Servo_Init();
	DC_Init();
	Ultrasonic_Init();
	
	// Port Settings
	DDRB|= 0x30;		// DC motor(PB4), Servo Motor(PB5) Port Output 00110000
	DDRC = 0x18;		// LED(PC3), UlatraSonic Trigger(PC4) Port Output 00011000
	DDRF = 0x00;		// PF(Sensor) PIN Output (PF0 : adc, PF1: cds, PF3 : thermister, PF6 : gas, PF7 : pressure)
	
	// variables for sensing
	double lux;
	double filtered_lux;
	double adc;
	double filtered_adc;
	double temperature;
	double filtered_tem;
	double gas;
	double filtered_gas;
	double pressure;
	double distance;
	double filtered_dis;
	double previous_filtered_dis = 0;
	double velocity;
	
	MAF_Filter lux_filter;
	MAF_Filter gas_filter;
	Kalman_Filter Ultrasonic_filter;
	FIR_Filter adc_filter;
	IIR_Filter pre_filter;
	IIR_Filter tem_filter;
	MAF_Init(&lux_filter);
	MAF_Init(&gas_filter);
	Kalman_Init(&Ultrasonic_filter, distance, 1.0);
	FIR_Init(&adc_filter);
	IIR_Init(&pre_filter);
	IIR_Init(&tem_filter);
	
	// FIR filter Coefficient
 	adc_filter.taps[0] = 0.1;
 	adc_filter.taps[1] = 0.1;
 	adc_filter.taps[2] = 0.1;
 	adc_filter.taps[3] = 0.1;
 	adc_filter.taps[4] = 0.1;
 	adc_filter.taps[5] = 0.1;
 	adc_filter.taps[6] = 0.1;
 	adc_filter.taps[7] = 0.1;
 	adc_filter.taps[8] = 0.1;
 	adc_filter.taps[9] = 0.1;
	
	// Enable all interrupt
	sei();
	
	// Loop
	while (1)
	{
		// Sensing
		adc = ConvertToPercentage(ADC_read(0));
		lux = ConvertToLux(ADC_read(1));
		temperature = ConvertToTem(ADC_read(3));
		gas = ConvertToPpm(ADC_read(6));
		pressure = ConvertToPre(ADC_read(7));
		distance = getEcho();
		
		// Filtering
		filtered_lux = MAF_Update(&lux_filter, lux);
		filtered_gas = MAF_Update(&gas_filter, gas);
		filtered_dis = Kalman_Update(&Ultrasonic_filter, distance);
		filtered_pre = IIR_Filtering(&pre_filter, pressure);
		filtered_adc = FIR_Filtering(&adc_filter, adc);
		filtered_tem = IIR_Filtering(&tem_filter, temperature);
		
		// Calculate Velocity
		velocity = (previous_filtered_dis - filtered_dis) / 0.5;	// Interval Time = 0.5s
		
		//Uart
		//USART_Transnum();
		
		// Update previous distance
		previous_filtered_dis = filtered_dis;
		
		// Ultrasonic
		if(distance < 20){
			set_led(255-(filtered_lux*10), 1);
		}else if(distance < 40){
			set_led(255-(filtered_lux*10), 3);
		}else{
			set_led(255-(filtered_lux*10), 2);
		}
		
		// Thermister
		if(filtered_tem > 27.5){
			DC_speed(filtered_adc/4);
		}else{
			DC_speed(0);
		}
		
		// Gas Sensor
		if(filtered_gas > 9.83){
			BuzzerOn(filtered_gas * 10, filtered_gas);
		}else{
			BuzzerOff();
		}
		
		// delay 0.5s
		_delay_ms(500);
	}
}

// Timer Overflow Interrupt(Servo Motor)
ISR(TIMER1_OVF_vect){
	if(filtered_pre > 10){
		set_servo(90);
		}else{
		set_servo(0);
	}
}