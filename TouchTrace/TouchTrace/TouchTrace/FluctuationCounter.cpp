//
//  FluctuationCounter.cpp
//  TouchTrace
//
//  Created by Nobuhiro Kuroiwa on 2014/03/05.
//  Copyright (c) 2014年 Nobuhiro Kuroiwa. All rights reserved.
//

#include "FluctuationCounter.h"

FluctuationCounter::FluctuationCounter()
{
	_oldVec = {0.0};
	_newVec = {0.0};
}

FluctuationCounter::~FluctuationCounter()
{
	
}

void FluctuationCounter::Input(const MODELVEC3D& vec)
{
	_oldVec = _newVec;
	_newVec = vec;
}

MODELFLOAT FluctuationCounter::Fluctuation()
{
	return 0.0;
}