#ifndef KALMAN_H_
#define KALMAN_H_

#define Q 0.1
#define R 1.0

typedef struct {
	double x;       // State variable
	double P;       // Error covariance
	double K;       // Kalman Gain
} Kalman_Filter;

void Kalman_Init(Kalman_Filter* filter, double initial_x, double initial_P) {
	filter->x = initial_x;
	filter->P = initial_P;
	filter->K = 0.0;
}

double Kalman_Update(Kalman_Filter* filter, double measurement) {
	// Predict
	double x_hat = filter->x;
	double P_hat = filter->P + Q;

	// Measure
	filter->K = P_hat / (P_hat + R);
	filter->x = x_hat + filter->K * (measurement - x_hat);
	filter->P = (1 - filter->K) * P_hat;

	return filter->x;
}
#endif /* KALMAN_H_ */