#define LED_R PE3
#define LED_G PE4
#define LED_B PE5
#define BV(n) (1 << n)

#ifndef LED_H_
#define LED_H_

// Settings for 3colors LED
void LED_Init() {
	// LED 핀들을 출력으로 설정
	DDRE |= (1 << LED_R) | (1 << LED_G) | (1 << LED_B);

	TCCR3A |= BV(WGM30) | BV(COM3A1) | BV(COM3B1) | BV(COM3C1);
	TCCR3B |= BV(WGM32) | BV(CS31);
}

// LED(red, green, blue) -> parameters are brightness of each colors
void led(unsigned short red, unsigned short green, unsigned short blue){
	OCR3A = red & 255;
	OCR3B = green & 255;
	OCR3C = blue & 255;
}

// set led
void set_led(short brightness, unsigned short color){
	if(brightness <= 0){
		led(0, 0, 0);
	}else{
		if(color == 1){
			led(brightness, 0, 0);
			}else if(color == 2){
			led(0, brightness, 0);
			}else if(color == 3){
			led(0, 0, brightness);
		}
	}
}

#endif /* LED_H_ */