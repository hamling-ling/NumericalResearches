#pragma once

#define MODEL_DELTA_T		0.033f

namespace pekomodel {

	typedef double MODELFLOAT;

	typedef struct {
		MODELFLOAT theta;
		MODELFLOAT omega;
	} SOLUTION;

	class PekoModel
	{
	public:
		PekoModel(void);
		virtual ~PekoModel(void);

		void GetNext();
		SOLUTION* GetSolution(SOLUTION* sln);
		void Reset(MODELFLOAT newTheta, MODELFLOAT newOmega);

	private:

		// constants
		const MODELFLOAT dt;

		// fields
		MODELFLOAT t;
		MODELFLOAT theta;
		MODELFLOAT omega;

		MODELFLOAT EulerMethod(const MODELFLOAT rhs, const MODELFLOAT x);
		MODELFLOAT Funcs0(MODELFLOAT t, MODELFLOAT theta, MODELFLOAT omega);
		MODELFLOAT Funcs1(MODELFLOAT t, MODELFLOAT theta, MODELFLOAT omega);
	};

}
