//
//  FluctuationCounter.h
//  TouchTrace
//
//  Created by Nobuhiro Kuroiwa on 2014/03/05.
//  Copyright (c) 2014年 Nobuhiro Kuroiwa. All rights reserved.
//

#ifndef __TouchTrace__FluctuationCounter__
#define __TouchTrace__FluctuationCounter__

#include "modeltool.h"

using namespace osakanamodel;

class FluctuationCounter
{
public:
	FluctuationCounter();
	~FluctuationCounter();
	
    void Begin(const MODELPOINT& point);
    void Move(const MODELPOINT& point);
	MODELFLOAT End(const MODELPOINT& point);
	
private:
	MODELPOINT _oldPoint;
	MODELPOINT _newPoint;
    const MODELPOINT kStdVec;
};

#endif /* defined(__TouchTrace__FluctuationCounter__) */
