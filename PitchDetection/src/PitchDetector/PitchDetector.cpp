#include "PitchDetector.h"
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
	_m = new double[_samplingSize];
	_x2 = new double[_samplingSize];
	_nsdf = new double[_samplingSize];
}

bool PitchDetector::Detect(double* x)
{
	if (!_corr) {
		return false;
	}


}

bool PitchDetector::ComputeNsdf(double* x)
{
	const int N = _samplingSize;

	_corr->Compute(x, _r);
	for (int t = 0; t < N; t++) {
		_x2[t] = x[t] * x[t];
	}

	for (int t = 0; t < N; t++) {

		for (int j = 0; j < N; j++) {
			_m[t] = _m[t] + _x2[j] + _x2[j + t];
		}
	}

	for (int t = 0; t < N; t++) {
		_nsdf[t] = 2.0 * _r[t] / _m[t];
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

	return 1;
}
