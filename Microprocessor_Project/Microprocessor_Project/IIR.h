#define IIR_ALPHA 0.2

#ifndef IIRFILTER_H_
#define IIRFILTER_H_

typedef struct {
	double prevOutput;
} IIR_Filter;

// IIR reset
void IIR_Init(IIR_Filter* filter) {
	filter->prevOutput = 0.0;
}

// IIR filtering
double IIR_Filtering(IIR_Filter* filter, double sample) {
	double output = IIR_ALPHA * sample + (1 - IIR_ALPHA) * filter->prevOutput;
	filter->prevOutput = output;
	return output;
}

#endif /* IIRFILTER_H_ */