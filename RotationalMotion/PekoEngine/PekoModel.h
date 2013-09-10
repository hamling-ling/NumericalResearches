#pragma once

#include "ModelType.h"

using namespace osakanamodel;

namespace pekomodel {

	class PekoModel
	{
	public:
		PekoModel();
		virtual ~PekoModel(void);

		void GetNext();
		SOLUTION* GetSolution(SOLUTION* sln, double scale);
		void Reset(MODELFLOAT newTheta, MODELFLOAT newOmega);

	private:

		// constants
		const MODELFLOAT dt;

		// fields
		MODELFLOAT _t;
		MODELFLOAT _theta;
		MODELFLOAT _omega;
		MODELPOINT _points[MODEL_POINTS_LEN];
		MODELFLOAT _scale;

		MODELFLOAT Funcs0(const MODELFLOAT t, const MODELFLOAT omega, const MODELFLOAT theta);
		MODELFLOAT Funcs1(const MODELFLOAT t, const MODELFLOAT omega, const MODELFLOAT theta);
		ModelPoint* ComputeLine(double input, double scale);
		double LineFunc(double x, double w, double c1, double c2, double c3, double c4);
	};

}
