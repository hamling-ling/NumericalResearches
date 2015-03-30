#pragma once

#include <memory>

class AutoCorrelation;

typedef enum Note_ {
	A,
	Bes,
	B,
	C,
	Cis,
	D,
	Dis,
	E,
	F,
	Fis,
	G,
	Gis,
} Note;

typedef struct PitchInfo_ {
	double freq;
	Note note;
	const char* noteStr;
	uint32_t octave;
} PitchInfo;

class PitchDetector
{
public:
	PitchDetector(int samplingRate, int samplingSize);
	virtual ~PitchDetector();
	bool Initialize();
	bool Detect(double* x);
	void GetPiatch(PitchInfo& pitch);

private:
	const int _samplingRate;
	const int _samplingSize;
	std::shared_ptr<AutoCorrelation> _corr;
	double* _r;
	double* _m;
	double* _x2;
	double* _nsdf;
	PitchInfo _pitch;

	bool ComputeNsdf(double* x);
	int AnalyzeNsdf();
};
