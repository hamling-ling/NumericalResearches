#pragma once

#define MODEL_DELTA_T		0.033

namespace pekomodel {

	typedef double MODELFLOAT;

	typedef struct {
		MODELFLOAT theta;
		MODELFLOAT omega;
		MODELFLOAT t;
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
		MODELFLOAT _t;
		MODELFLOAT _theta;
		MODELFLOAT _omega;

		MODELFLOAT Funcs0(const MODELFLOAT t, const MODELFLOAT omega, const MODELFLOAT theta);
		MODELFLOAT Funcs1(const MODELFLOAT t, const MODELFLOAT omega, const MODELFLOAT theta);
	};

}
