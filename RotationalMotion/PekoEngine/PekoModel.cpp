#include "stdafx.h"
#include "PekoModel.h"
#include <cfloat>
#include <cstring>
#include <pthread.h>
#define _USE_MATH_DEFINES
#include <math.h>

#ifdef _DEBUG
#include <iostream> // for printf debug
#endif

#define RUNGE_KUTTA

using namespace std;

#define ZEROMEMORY(x)	memset(&x, 0, sizeof(x))

namespace pekomodel {

	PekoModel::PekoModel()
		:	dt(MODEL_DELTA_T)
	{
		Reset();
	}

	PekoModel::~PekoModel()
	{
	}

	void PekoModel::Reset()
	{
		_theta = 0.0f;
		_omega = 0.0f;
		_t = 0;
		memset(_points, 0, sizeof(_points));

		_points[0].x = 0.0f;
		_points[0].y = 0.0f;
		_points[1].x = 1.0f;
		_points[1].y = 0.0f;
		_points[2].x = 1.0f;
		_points[2].y = 1.0f;
		_points[3].x = 0.0f;
		_points[3].y = 1.0f;
	}

	void PekoModel::GetNext()
	{
		_t += dt;
	}

	SOLUTION* PekoModel::GetSolution(SOLUTION* sln, double scale)
	{
		sln->theta	= _theta;
		sln->omega	= _omega;
		sln->t		= _t;
		memcpy(sln->points, _points, sizeof(_points));

		return sln;
	}

	// domega/dt
	MODELFLOAT PekoModel::Funcs0(const MODELFLOAT t, const MODELFLOAT omega, const MODELFLOAT theta)
	{
		MODELFLOAT domega_dt = 0.0;

		return domega_dt;
	}

	// dtheta/dt
	MODELFLOAT PekoModel::Funcs1(const MODELFLOAT t, const MODELFLOAT omega, const MODELFLOAT theta)
	{
		return omega;
	}
}
