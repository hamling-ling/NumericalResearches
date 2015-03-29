// NsdfCompute.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "AutoCorrelation.h"

/*
#include <cstdio>
#include <complex.h> // complex.h は fftw3.h より先に include する
#include <fftw3.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>*/

#pragma comment(lib, "libfftw3-3.lib")

using namespace std;
/*
void autocorrelation(double(&x)[1024], double(&corr)[1024])
{
	static const int	fftSize = 1024;
	static const int	fftSize2 = fftSize/2;

	fftw_complex* in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * fftSize);
	fftw_complex* out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * fftSize);
	fftw_complex* in2 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * fftSize);
	double* out2 = &(corr[0]);

	fftw_plan plan_fft = fftw_plan_dft_r2c_1d(fftSize, &(x[0]), out, FFTW_ESTIMATE);
	fftw_execute(plan_fft);
	fftw_destroy_plan(plan_fft);

	for (int i = 0; i < fftSize; i++) {
		double powered = out[i][0] * out[i][0] + out[i][1] * out[i][1];
		in2[i][0] = powered / 1024;
		in2[i][1] = 0.0f;
	};

	fftw_plan plan_ifft = fftw_plan_dft_c2r_1d(fftSize, in2, out2, FFTW_ESTIMATE);
	fftw_execute(plan_ifft);
	fftw_destroy_plan(plan_ifft);

	fftw_free(in);
	fftw_free(in2);
	fftw_free(out);
}*/

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc < 1) {
		wcout << "need to specify csv file in command-line paremeter" << endl;
		return 1;
	}

	ifstream file(argv[1]);
	if (!file.is_open()) {
		wcout << "can't open " << argv[1] << endl;
		return 1;
	}

	string line;
	const int dataNum = 1024;
	double data[dataNum] = { 0 };
	int index = 0;
	while (getline(file, line) && index < dataNum) {
		istringstream iss(line);
		double x;
		if (!(iss >> x)) {
			cout << "can't convert " << line << " to double" << endl;
			return 1;
		}
		data[index++] = x;
	}
	file.close();

	double corr[1024] = { 0 };
	//autocorrelation(data, corr);

	AutoCorrelation autoCorr(1024);
	autoCorr.Compute(data, corr);
	for (int i = 0; i < 10; i++) {
		cout << "r[" << i << "] = " << corr[i] << endl;
 	}

	return 0;
}

