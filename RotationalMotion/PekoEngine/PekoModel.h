#pragma once

#include "ModelType.h"
#include "modeltool.h"

using namespace osakanamodel;

namespace pekomodel {

	class PekoModel
	{
	public:
		PekoModel();
		virtual ~PekoModel(void);

		void GetNext();
		SOLUTION* GetSolution(SOLUTION* sln, double scale);
		void Reset();

	private:

		// constants
		const MODELFLOAT dt;

		// fields
		MODELFLOAT _t;
		MODELVEC3D _theta;
		MODELVEC3D _omega;
		MODELVEC3D _points[MODEL_POINTS_LEN];
		MODELVEC3D _v;
		MODELVEC3D _x;

		MODELFLOAT Func0(const MODELFLOAT t, const MODELFLOAT omega, const MODELFLOAT theta);
		MODELFLOAT Func1(const MODELFLOAT t, const MODELFLOAT omega, const MODELFLOAT theta);
	};

}
