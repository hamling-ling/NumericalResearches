#include "PitchDetector.h"

#include <iostream>
#include <cmath>
#include "NsdfCompute/AutoCorrelation.h"
#include "NsdfWalker/NsdfWalker.h"

using namespace std;
using namespace osakanaengine;

static const float kNoteConst = log10(pow(2.0f, 1.0f / 12.0f));
const char* kNoteStrings[] {
	"A", "Bes", "B", "C",
		"Cis", "D", "Dis", "E",
		"F", "Fis", "G", "Gis",
};

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
	_r = new float[_samplingSize];
	if (_r == NULL) {
		return false;
	}

	_m = new float[_samplingSize];
	if (_m == NULL) {
		return false;
	}

	_x2 = new float[_samplingSize];
	if (_x2 == NULL) {
		return false;
	}

	_nsdf = new float[_samplingSize];
	if (_nsdf == NULL) {
		return false;
	}

	return true;
}

bool PitchDetector::Detect(float* x)
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

void PitchDetector::GetPiatch(PitchInfo& pitch)
{
	pitch = _pitch;
}

bool PitchDetector::ComputeNsdf(float* x)
{
	const int N = _samplingSize;

	// auto correlation
	_corr->Compute(x, _r);

	// x^2
	for (int t = 0; t < N; t++) {
		_x2[t] = x[t] * x[t];

		// debug
		//std::cout << "r[" << t << "]=" << _r[t] << endl;
		//std::cout << "x2[" << t << "]=" << _x2[t] << endl;
	}

	// m(t)
	memset(_m, 0, sizeof(float)* N);
	for (int t = 0; t < N; t++) {
		for (int j = 0; j < N - t; j++) {
			_m[t] = _m[t] + _x2[j] + _x2[j + t];
		}
	}

	// nsdf
	for (int t = 0; t < N; t++) {
		_nsdf[t] = 2.0f * _r[t] / _m[t];

		// debug
		//std::cout << "nsdf[" << t << "]=" << _nsdf[t] << endl;
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

	if (keyMaxs[0].index == 0.0) {
		return -1;
	}

	float freq = _samplingRate/static_cast<float>(keyMaxs[0].index);

	float dnote = log10(freq / 27.5f) / kNoteConst;
	int inote = static_cast<int>(0.5f + dnote);

	_pitch.note = static_cast<Note>(inote);
	_pitch.noteStr = kNoteStrings[inote % 12];
	_pitch.octave = inote / 12;
	_pitch.freq = freq;

	return inote;
}
