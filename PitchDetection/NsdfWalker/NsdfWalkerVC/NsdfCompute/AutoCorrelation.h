#pragma once

#include <fftw3.h>

#pragma comment(lib, "libfftw3-3.lib")

class AutoCorrelation
{
public:
	AutoCorrelation(int windowSize);
	virtual ~AutoCorrelation();
	void Compute(double* x, double *corr);
	double WindowSize();
private:
	const int kWinSize;
	const int kFftSize;
	double* _src;
	fftw_complex* _fft;
	fftw_complex* _powspec;
	double* _ifft;
};

