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

using namespace std;

#define ZEROMEMORY(x)	memset(&x, 0, sizeof(x))

namespace pekomodel {

	static const MODELFLOAT kKa		= 0.707f;
	static const MODELFLOAT kKl		= 10.0f;
	static const MODELFLOAT kKd		= 2.9f;
	static const MODELFLOAT kTheta	= M_PI/2.0f;
	static const MODELFLOAT kR		= 1.0f;
	static const MODELFLOAT kI		= 1.0f;

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
		theta = newTheta;
		omega = newOmega;
	}

	void PekoModel::GetNext()
	{
		//MODELFLOAT totangle = kTheta + theta;

		//MODELFLOAT xa = 2.0f * kR * sin(kTheta/2.0f);
		//MODELFLOAT xb = 2.0f * kR * sin(totangle/2.0f);
		//MODELFLOAT displ = xb - xa;

		//MODELFLOAT Fl = kKl * displ;
		//MODELFLOAT tau_l = kR * Fl * (-1.0f) * sin((M_PI + totangle)/2.0f);

		//MODELFLOAT tau_a = - kKa * totangle;

		//MODELFLOAT dtheta_dt = (tau_a +  tau_l)/kI - kKd * omega;
		//MODELFLOAT domega_dt = omega;

		//MODELFLOAT nextheta = EulerMethod(dtheta_dt, theta);
		//MODELFLOAT nexomega = EulerMethod(domega_dt, omega);

		//theta = nextheta;
		//omega = nexomega;

		MODELFLOAT k1_theta=Funcs0(t, theta, omega);
		MODELFLOAT k1_omega=Funcs1(t, theta, omega);
		MODELFLOAT k2_theta=Funcs0(t+dt/2, theta+dt*k1_theta/2, omega+dt*k1_omega/2);
		MODELFLOAT k2_omega=Funcs1(t+dt/2, theta+dt*k1_theta/2, omega+dt*k1_omega/2);
		MODELFLOAT k3_theta=Funcs0(t+dt/2, theta+dt*k2_theta/2, omega+dt*k2_omega/2);
		MODELFLOAT k3_omega=Funcs1(t+dt/2, theta+dt*k2_theta/2, omega+dt*k2_omega/2);
		MODELFLOAT k4_theta=Funcs0(t+dt, theta+dt*k3_theta, omega+dt*k3_omega);
		MODELFLOAT k4_omega=Funcs1(t+dt, theta+dt*k3_theta, omega+dt*k3_omega);

		//x[j] += (k1[j] + 2*k2[j] + 2*k3[j] + k4[j])*h/6;
		theta += dt*(k1_theta + 2*k2_theta + 2*k3_theta + k4_theta)/6.0;
		omega += dt*(k1_omega + 2*k2_omega + 2*k3_omega + k4_omega)/6.0;
		t += dt;
	}

	SOLUTION* PekoModel::GetSolution(SOLUTION* sln)
	{
		sln->theta = theta;
		sln->omega = omega;
		return sln;
	}

	MODELFLOAT PekoModel::EulerMethod(const MODELFLOAT rhs, const MODELFLOAT x)
	{
		MODELFLOAT xNext = rhs * dt + x;

		return xNext;
	}

	MODELFLOAT PekoModel::Funcs0(MODELFLOAT t, MODELFLOAT theta, MODELFLOAT omega)
	{
		MODELFLOAT totangle = kTheta + theta;

		MODELFLOAT xa = 2.0f * kR * sin(kTheta/2.0f);
		MODELFLOAT xb = 2.0f * kR * sin(totangle/2.0f);
		MODELFLOAT displ = xb - xa;

		MODELFLOAT Fl = kKl * displ;
		MODELFLOAT tau_l = kR * Fl * (-1.0f) * sin((M_PI + totangle)/2.0f);

		MODELFLOAT tau_a = - kKa * theta;

		MODELFLOAT dtheta_dt = (tau_a +  tau_l)/kI - kKd * omega;

		return dtheta_dt;
	}

	MODELFLOAT PekoModel::Funcs1(MODELFLOAT t, MODELFLOAT theta, MODELFLOAT omega)
	{
		return omega;
	}

}
