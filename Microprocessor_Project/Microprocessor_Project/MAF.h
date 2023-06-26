#ifndef INCFILE1_H_
#define INCFILE1_H_

#define MAF_SIZE 10

typedef struct {
	double samples[MAF_SIZE];
	unsigned short index;
	double sum;
} MAF_Filter;

// MAF reset
void MAF_Init(MAF_Filter* filter) {
	for (int i = 0; i < MAF_SIZE; i++) {
		filter->samples[i] = 0;
	}
	filter->index = 0;
	filter->sum = 0.0;
}

// MAF filtering
double MAF_Update(MAF_Filter* filter, double sample) {
	filter->sum -= filter->samples[filter->index];
	filter->samples[filter->index] = sample;
	filter->sum += sample;
	
	filter->index++;
	if (filter->index >= MAF_SIZE) {
		filter->index = 0;
	}
	
	return filter->sum / MAF_SIZE;
}

#endif /* INCFILE1_H_ */