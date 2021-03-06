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
	bool error;
	float freq;
	Note note;
	const char* noteStr;
	uint8_t octave;
} PitchInfo;

class PitchDetector
{
public:
	PitchDetector(int samplingRate, int samplingSize);
	virtual ~PitchDetector();
	bool Initialize();
	bool Detect(float* x);
	bool Detect(int16_t* x);
	void GetPiatch(PitchInfo& pitch);

private:
	const int _samplingRate;
	const int _samplingSize;
	std::shared_ptr<AutoCorrelation> _corr;
	float* _r;
	float* _m;
	float* _x;
	float* _x2;
	float* _nsdf;
	PitchInfo _pitch;

	bool ComputeNsdf(float* x, float* x2);
	int AnalyzeNsdf();
};
