#define FIR_TAP_NUM 10

#ifndef FIRFILTER_H_
#define FIRFILTER_H_

typedef struct {
	double taps[FIR_TAP_NUM];
	double samples[FIR_TAP_NUM];
	unsigned short index;
} FIR_Filter;

// FIR reset
void FIR_Init(FIR_Filter* filter) {
	for (int i = 0; i < FIR_TAP_NUM; i++) {
		filter->taps[i] = 0.0;
		filter->samples[i] = 0.0;
	}
	filter->index = 0;
}

// FIR filtering
double FIR_Filtering(FIR_Filter* filter, double sample) {
	filter->samples[filter->index] = sample;
	
	double output = 0.0;
	unsigned short i = filter->index;
	
	for (int j = 0; j < FIR_TAP_NUM; j++) {
		output += filter->taps[j] * filter->samples[i];
		if (i == 0) {
			i = FIR_TAP_NUM - 1;
			} else {
			i--;
		}
	}
	filter->index++;
	if (filter->index >= FIR_TAP_NUM) {
		filter->index = 0;
	}
	return output;
}

		/*
		쓸 때 메인에다가 
		firFilter.taps[0] = 0.2;
		firFilter.taps[1] = 0.2;
		firFilter.taps[2] = 0.2;
		firFilter.taps[3] = 0.2;
		firFilter.taps[4] = 0.2; 
		이렇게 차수마다 계수 설정 필요!!
		*/

#endif /* FIRFILTER_H_ */