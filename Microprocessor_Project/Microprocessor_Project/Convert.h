#ifndef CDS_H_
#define CDS_H_

#include <math.h>

#define R9 4700.0
#define R10 4700.0
#define B 3650.0
#define T0 25.0
#define R0 1000.0
#define RL 330
#define a 574.25
#define b -2.222

double ConvertToLux(unsigned short adcValue){
	// Unit : Lux
	double gamma = 1.0;
	double voltage = ((double)adcValue / 1023) * 5.0;		// 5V 기준 adcValue를 전압으로 변환
	double Rcds = ((R9 * 5.0)/voltage) - R9;
	double lux = pow(10,1-((log10(Rcds)-log10(40000))/gamma));
	
	return lux;
}

double FindGamma(double x, unsigned short adcValue){
	double voltage = ((double)adcValue / 1023) * 5.0;
	double Rcds = ((R9 * 5.0)/voltage) - R9;
	double gamma = (log10(Rcds)-log10(40000))/(log10(10) - log10(x));	// 실제 조도계로 64lux
	
	return gamma;
}

double ConvertToTem(unsigned short adcValue){
	// Unit : Celcius
	double voltage = ((double)adcValue / 1023.0) * 5.0;		// 4.203323558
	double Rth = ((5.0 / voltage) * R10) - R10;				//890.8139537
	double T = 1.0/((1.0/(T0 + 273.15)) + ((1.0/B) * log(Rth/R0)));		
	
	return T - 273.15;
}

double ConvertToPre(unsigned short adcValue){
	// Unit : N
	// 0.2N ~ 20N
	return (adcValue / 1023.0) * 20.0;
}

double ConvertToPercentage(unsigned short adcValue){
	// Unit : %
	return ((double)adcValue / 1024) * 100;
}

double ConvertToPpm(unsigned short adcValue){
	// Unit : ppm
	double voltage = ((double)adcValue / 1023.0) * 5.0;
	double Rs = ((RL * 5.0)/voltage) - RL;
	double ratio = Rs / R0;
	double ppm = a * ratio * b;		// a = 574.25, b = -2.222
	
	return ppm;
}

#endif /* CDS_H_ */