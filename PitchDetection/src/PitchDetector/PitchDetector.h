#pragma once

#include <memory>

class AutoCorrelation;

class PitchDetector
{
public:
	PitchDetector(int samplingRate, int samplingSize);
	bool Initialize();
	bool Detect(double* x);
	virtual ~PitchDetector();
private:
	const int _samplingRate;
	const int _samplingSize;
	std::shared_ptr<AutoCorrelation> _corr;
	double* _r;
	double* _m;
	double* _x2;
	double* _nsdf;

	bool ComputeNsdf(double* x);
	int AnalyzeNsdf();
};
