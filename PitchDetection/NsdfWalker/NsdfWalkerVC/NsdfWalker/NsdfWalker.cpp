#include "stdafx.h"
#include "NsdfWalker.h"


NsdfWalker::NsdfWalker(uint32_t strides)
	: _strides(strides), _state(NsdfWalkerStateSearching1stBell), _bells(0)
{
	_strideMax.reserve(strides);
	memset(&_maximum, 0, sizeof(_maximum));
}


NsdfWalker::~NsdfWalker()
{
}
