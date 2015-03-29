#include "stdafx.h"
#include "AutoCorrelation.h"
#include <fftw3.h>
#include <memory>

AutoCorrelation::AutoCorrelation(int windowSize)
	: kWinSize(windowSize), kFftSize(windowSize*2), _src(NULL), _fft(NULL), _powspec(NULL)
{
	_src = static_cast<double*>(fftw_malloc(sizeof(double) * kFftSize));
	_fft = static_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * kFftSize));
	_powspec = static_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * kFftSize));
	_ifft = static_cast<double*>(fftw_malloc(sizeof(double) * kFftSize));
}

AutoCorrelation::~AutoCorrelation()
{
	fftw_free(_src);
	fftw_free(_fft);
	fftw_free(_powspec);
	fftw_free(_ifft);
}

void AutoCorrelation::Compute(double* x, double *corr)
{
	memset(_src, 0, kFftSize);
	memset(_fft, 0, sizeof(fftw_complex) * kFftSize);
	memset(_powspec, 0, sizeof(fftw_complex) * kFftSize);

	// padding 0 half of src
	memcpy(_src, x, sizeof(double)*kWinSize);

	// fft
	fftw_plan plan_fft = fftw_plan_dft_r2c_1d(kFftSize, _src, _fft, FFTW_ESTIMATE);
	fftw_execute(plan_fft);
	fftw_destroy_plan(plan_fft);
	
	// power spectrum
	for (int i = 0; i < kFftSize; i++) {
		double powered = _fft[i][0] * _fft[i][0] + _fft[i][1] * _fft[i][1];
		_powspec[i][0] = powered / kFftSize;
		_powspec[i][1] = 0.0f;
	};
	
	// ifft
	fftw_plan plan_ifft = fftw_plan_dft_c2r_1d(kFftSize, _powspec, _ifft, FFTW_ESTIMATE);
	fftw_execute(plan_ifft);
	fftw_destroy_plan(plan_ifft);

	memcpy(corr, _ifft, sizeof(double)*kWinSize);
}

double AutoCorrelation::WindowSize()
{
	return kWinSize;
}
