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

	static const MODELFLOAT kKa		= 7.052225;
	static const MODELFLOAT kKl		= 100.0;
	static const MODELFLOAT kKd		= 2.9;
	static const MODELFLOAT kTheta	= M_PI/2.0;
	static const MODELFLOAT kR		= 1.0;
	static const MODELFLOAT kI		= 1.0;
	static const MODELFLOAT kThetaLim = M_PI * 1.5 / 2.0;

	PekoModel::PekoModel()
		:	dt(MODEL_DELTA_T)
	{
		Reset(0.0, 0.0);
	}

	PekoModel::~PekoModel()
	{
	}

	void PekoModel::Reset(MODELFLOAT newTheta, MODELFLOAT newOmega)
	{
		_theta = newTheta;
		_omega = newOmega;
		_t = 0;
		memset(_points, 0, sizeof(_points));
	}

	void PekoModel::GetNext()
	{
#ifdef RUNGE_KUTTA

		MODELFLOAT k1_omega = Funcs0(_t,		_omega,					_theta);
		MODELFLOAT k1_theta = Funcs1(_t,		_omega,					_theta);
		MODELFLOAT k2_omega = Funcs0(_t+dt/2.0,	_omega+dt*k1_omega/2.0,	_theta+dt*k1_theta/2.0);
		MODELFLOAT k2_theta = Funcs1(_t+dt/2.0,	_omega+dt*k1_omega/2.0,	_theta+dt*k1_theta/2.0);
		MODELFLOAT k3_omega = Funcs0(_t+dt/2.0,	_omega+dt*k2_omega/2.0,	_theta+dt*k2_theta/2.0);
		MODELFLOAT k3_theta = Funcs1(_t+dt/2.0,	_omega+dt*k2_omega/2.0,	_theta+dt*k2_theta/2.0);
		MODELFLOAT k4_omega = Funcs0(_t+dt,		_omega+dt*k3_omega,		_theta+dt*k3_theta);
		MODELFLOAT k4_theta = Funcs1(_t+dt,		_omega+dt*k3_omega,		_theta+dt*k3_theta);

		_omega += dt*(k1_omega + 2.0*k2_omega + 2.0*k3_omega + k4_omega)/6.0;
		_theta += dt*(k1_theta + 2.0*k2_theta + 2.0*k3_theta + k4_theta)/6.0;
#else
		MODELFLOAT domega_dt = Funcs0(_t,		_omega,					_theta);
		MODELFLOAT dtheta_dt = Funcs1(_t,		_omega,					_theta);

		_omega *= dt*domega_dt;
		_theta += dt*dtheta_dt;
#endif
		_t += dt;
	}

	SOLUTION* PekoModel::GetSolution(SOLUTION* sln, double scale)
	{
		sln->theta	= _theta;
		sln->omega	= _omega;
		sln->t		= _t;

		ComputeLine(_theta/kThetaLim, scale);
		memcpy(sln->points, _points, sizeof(_points));

		return sln;
	}

	// domega/dt
	MODELFLOAT PekoModel::Funcs0(const MODELFLOAT t, const MODELFLOAT omega, const MODELFLOAT theta)
	{
		MODELFLOAT totangle = kTheta + theta;

		MODELFLOAT xa = 2.0 * kR * sin(kTheta/2.0);
		MODELFLOAT xb = 2.0 * kR * sin(totangle/2.0);
		MODELFLOAT displ = xb - xa;

		MODELFLOAT Fl = kKl * displ;
		MODELFLOAT tau_l = kR * Fl * (-1.0) * sin((M_PI + totangle)/2.0);

		MODELFLOAT tau_a = - kKa * theta;

		MODELFLOAT domega_dt = (tau_a + tau_l)/kI - kKd * omega;

		return domega_dt;
	}

	// dtheta/dt
	MODELFLOAT PekoModel::Funcs1(const MODELFLOAT t, const MODELFLOAT omega, const MODELFLOAT theta)
	{
		return omega;
	}

	// input must be between [0,1]
	ModelPoint* PekoModel::ComputeLine(double input, double scale)
	{
		double w = 100.0 + 50.0*input;
		double s = 3.0 - 3.0*input;

		double c1 = w/2.0;
		double c2 = -w/12.0 - 2.0*s;
		double c3 = s;
		double c4 = 0;

		double dx = 1.0 / (MODEL_POINTS_LEN-1);
		double x = 0;

		for(int i = 0; i < MODEL_POINTS_LEN/2+1; i++)
		{
			ModelPoint p = _points[i];
			p.x = x * scale;
			p.y = LineFunc(x, w, c1, c2, c3, c4) * scale;
			_points[i] = p;

			p.x = scale - p.x;
			_points[MODEL_POINTS_LEN - i - 1] = p;

			x += dx;
		}

		return _points;
	}

	double PekoModel::LineFunc(double x, double w, double c1, double c2, double c3, double c4)
	{
		double x2 = x*x;
		double x3 = x2*x;
		double x4 = x3*x;

		double y = -w * x4 / 24.0 +
					c1 * x3 / 6.0 +
					c2 * x2 / 2.0 +
					c3 * x +
					c4;
		return y;
	}
}
