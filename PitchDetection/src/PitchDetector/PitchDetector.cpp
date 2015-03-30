#include "PitchDetector.h"

#include <iostream>
#include "NsdfCompute/AutoCorrelation.h"
#include "NsdfWalker/NsdfWalker.h"

using namespace std;
using namespace osakanaengine;

PitchDetector::PitchDetector(int samplingRate, int samplingSize)
: 
_samplingRate(samplingRate),
_samplingSize(samplingSize),
_r(NULL), _m(NULL), _x2(NULL), _nsdf(NULL)
{
}

PitchDetector::~PitchDetector()
{
	delete(_r);
	delete(_m);
	delete(_x2);
	delete(_nsdf);
}

bool PitchDetector::Initialize()
{
	if (_corr) {
		return true;
	}

	_corr = std::make_shared<AutoCorrelation>(_samplingSize);
	_r = new double[_samplingSize];
	if (_r == NULL) {
		return false;
	}

	_m = new double[_samplingSize];
	if (_m == NULL) {
		return false;
	}

	_x2 = new double[_samplingSize];
	if (_x2 == NULL) {
		return false;
	}

	_nsdf = new double[_samplingSize];
	if (_nsdf == NULL) {
		return false;
	}

	return true;
}

bool PitchDetector::Detect(double* x)
{
	if (!_corr) {
		return false;
	}

	if (!ComputeNsdf(x)) {
		return false;
	}

	if (AnalyzeNsdf() == -1) {
		return false;
	}

	return true;
}

bool PitchDetector::ComputeNsdf(double* x)
{
	const int N = _samplingSize;

	// auto correlation
	_corr->Compute(x, _r);

	// x^2
	for (int t = 0; t < N; t++) {
		_x2[t] = x[t] * x[t];

		// debug
		std::cout << "r[" << t << "]=" << _r[t] << endl;
	}

	// m(t)
	memset(_m, 0, sizeof(double)* N);
	for (int t = 0; t < N; t++) {
		for (int j = 0; j < N; j++) {
			_m[t] = _m[t] + _x2[j] + _x2[j + t];
		}
	}

	// nsdf
	for (int t = 0; t < N; t++) {
		_nsdf[t] = 2.0 * _r[t] / _m[t];

		// debug
		std::cout << "nsdf[" << t << "]=" << _nsdf[t] << endl;
	}

	return true;
}

int PitchDetector::AnalyzeNsdf()
{
	NsdfWalker walker(_samplingSize);

	for (int t = 0; t < _samplingSize; t++) {
		walker.Input(_nsdf[t]);
	}

	vector<NsdfPoint> keyMaxs;
	walker.GetKeyMaximums(keyMaxs);
	if (keyMaxs.empty()) {
		return -1;
	}

	double freq = keyMaxs[0].index / _samplingRate;
	// t.b.d

	return 1;
}
