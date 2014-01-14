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
		_theta = ZEROVEC3D;
		_omega = ZEROVEC3D;
		_t = 0;
		_v = MODELVEC3DMake(0.0, 0.0, 0.0);
		_x = MODELVEC3DMake(0.0, 0.5, 0.0);

		memset(_points, 0, sizeof(_points));

		_points[0].x = -0.5f;
		_points[0].y = 0.0f;
		_points[1].x = 0.5f;
		_points[1].y = 0.0f;
		_points[2].x = 0.5f;
		_points[2].y = 1.0f;
		_points[3].x = -0.5f;
		_points[3].y = 1.0f;
	}

	void PekoModel::GetNext()
	{
		MODELVEC3D Fex = ZEROVEC3D;
		MODELVEC3D Tex = ZEROVEC3D;
		if(_t == 0.0) {
			Fex.y = 350.0;
			Tex = MODELVEC3DMake(0.0, 0.0, 10);
		}

		MODELVEC3D Ftot = ZEROVEC3D;
		MODELVEC3D Ttot = ZEROVEC3D;
		int hitPointIndex = 0;
		bool hit = false;
		for(int i = 0; i < MODEL_POINTS_LEN; i++) {
			if(_points[i].y < 0.0) {
				hit = true;
				hitPointIndex = i;
				break;
			}
		}

		_t += dt;

		AddVec(&G, &Fex, &Ftot);
		if(hit) {
			MODELVEC3D Ftot_old = Ftot;
			_v.y = -_v.y;
			_v.y = _v.y - _v.y*0.2; // decay
		}

		// dv/dt = F/m -> v = F/m * dt + v-
		MODELVEC3D Vnxt;
		ScaleVec(dt, &Ftot, &Vnxt);
		AddVec(&Vnxt, &_v, &Vnxt);

		// dx/dt = v -> x = v * dt - x-
		MODELVEC3D Xnxt;
		ScaleVec(dt, &Vnxt, &Xnxt); 
		AddVec(&Xnxt, &_x, &Xnxt);

		if(hit) {
			// w = (rxv)/r^2
			MODELVEC3D r = ZEROVEC3D;
			SubtVec(&_points[hitPointIndex], &_x, &r);
			MODELVEC3D dx = ZEROVEC3D;
			SubtVec(&Xnxt, &_x, &dx);
			MODELVEC3D v = ZEROVEC3D;
			ScaleVec(1.0/dt, &dx, &v);
			MODELVEC3D rxv = ZEROVEC3D;
			CrossProduct(&r, &v, &rxv);
			ScaleVec(1.0/pow(Magnitude(&r), 2.0), &rxv, &_omega);

			MODELVEC3D decay = ZEROVEC3D;
			ScaleVec(-0.2, &_omega, &decay);// decay
			SubtVec(&_omega, &decay, &_omega);
		}

		// domega/dt = tau/I -> w = tau/I * dt + w-
		MODELVEC3D Wnxt;
		AddVec(&Ttot, &Tex, &Ttot);
		ScaleVec(dt, &Ttot, &Wnxt);
		AddVec(&Wnxt, &_omega, &Wnxt);

		// dtheta/dt = omega -> theta = omega * dt + theta-
		MODELVEC3D Theta;
		ScaleVec(dt, &Wnxt, &Theta);
		AddVec(&Theta, &_theta, &Theta);

		MODELVEC3D dx, domega, dtheta;
		SubtVec(&Xnxt, &_x, &dx);
		SubtVec(&Wnxt, &_omega, &domega);
		SubtVec(&Theta, &_theta, &dtheta);

		for(int i = 0; i < MODEL_POINTS_LEN; i++) {
			AddVec(&(_points[i]), &dx, &(_points[i]));

			MODELVEC3D cg2pt, cg2ptrot;
			SubtVec(&(_points[i]), &Xnxt, &cg2pt);
			RotateAroundZ(&cg2pt, dtheta.z, &cg2ptrot);
			AddVec(&Xnxt, &cg2ptrot, &(_points[i]));
		}

		_v = Vnxt;
		_x = Xnxt;
		_omega = Wnxt;
		_theta = _theta;
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
	MODELFLOAT PekoModel::Func0(const MODELFLOAT t, const MODELFLOAT omega, const MODELFLOAT theta)
	{
		MODELFLOAT domega_dt = 0.0;

		return domega_dt;
	}

	// dtheta/dt
	MODELFLOAT PekoModel::Func1(const MODELFLOAT t, const MODELFLOAT omega, const MODELFLOAT theta)
	{
		return omega;
	}
}
