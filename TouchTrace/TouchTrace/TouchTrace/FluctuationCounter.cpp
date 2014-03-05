//
//  FluctuationCounter.cpp
//  TouchTrace
//
//  Created by Nobuhiro Kuroiwa on 2014/03/05.
//  Copyright (c) 2014年 Nobuhiro Kuroiwa. All rights reserved.
//

#include "FluctuationCounter.h"

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <math.h>

FluctuationCounter::FluctuationCounter()
: kStdVec(MODELPOINTMake(0.0f, 1.0f))
{
	_oldPoint = {0.0};
	_newPoint = {0.0};
}

FluctuationCounter::~FluctuationCounter()
{
}

void FluctuationCounter::Begin(const MODELPOINT& point)
{
    _oldPoint = MODELPOINTMake(0.0f, 0.0f);
    _newPoint = point;
}

void FluctuationCounter::Move(const MODELPOINT& point)
{
	_oldPoint = _newPoint;
	_newPoint = point;
}

MODELFLOAT FluctuationCounter::End(const MODELPOINT& vec)
{
	Move(vec);

    MODELPOINT lastVec = {0.0f};
    SubtPoint(&_newPoint, &_oldPoint, &lastVec);
    
    MODELFLOAT angle = AngleBetween(&kStdVec, &lastVec);
    
	return -angle/M_PI;
}