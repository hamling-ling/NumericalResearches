// PekoEngineNet.h

#pragma once
#include <PekoEngine.h>

using namespace System;
using namespace pekoengine;


using namespace System;
using namespace pekoengine;
using namespace System::Collections::Generic;

namespace PekoEngineNet {

	delegate void CallbackDelegate(void*, EngineEventArg);

	public ref class Solution
	{
	public:
		MODELFLOAT theta;
		MODELFLOAT omega;
		Solution();
		Solution(SOLUTION* sln);
	};

	public ref class PekoEngineNet
	{
	public:

		PekoEngineNet();
		~PekoEngineNet();
		int Initialize();

		Solution^ GetSolution();
		void Start();
		void Stop();
		void Reset(float newTheta, float newOmega);

	private:
		PekoEngine* m_pEngine;

	};
}