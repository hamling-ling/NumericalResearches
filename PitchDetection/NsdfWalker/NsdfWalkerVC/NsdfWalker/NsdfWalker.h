#pragma once

#include <vector>
#include <cstdint>

typedef enum NsdfWalkerState {
	NsdfWalkerStateSearching1stBell,
	NsdfWalkerStateWalkingOnBell,
	NsdfWalkerStateSearchingBell,
};

typedef struct NsdfPoint {
	double value;
	uint32_t index;
	uint32_t padding;
};

class NsdfWalker
{
public:
	NsdfWalker(uint32_t strides);
	virtual ~NsdfWalker();
	void input(double x);

private:
	const int _strides;
	int _bells;
	std::vector<NsdfPoint> _strideMax;
	NsdfPoint _maximum;
	NsdfWalkerState _state;
};
