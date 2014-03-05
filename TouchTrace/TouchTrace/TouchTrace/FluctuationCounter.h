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
	
	void Input(const MODELVEC3D& vec);
	MODELFLOAT Fluctuation();
	
private:
	MODELVEC3D _oldVec;
	MODELVEC3D _newVec;
};

#endif /* defined(__TouchTrace__FluctuationCounter__) */
