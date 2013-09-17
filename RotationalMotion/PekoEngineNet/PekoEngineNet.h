// PekoEngineNet.h

#pragma once
#include <PekoEngine.h>

#using "WindowsBase.dll"

using namespace System;
using namespace pekoengine;

using namespace System;
using namespace System::Windows;
using namespace pekoengine;
using namespace System::Collections::Generic;

namespace PekoEngineNet {

	delegate void CallbackDelegate(void*, EngineEventArg);

	public ref class Solution
	{
	public:
		MODELFLOAT theta;
		MODELFLOAT omega;
		MODELFLOAT t;

		//include followings to use Point
		//C:\Program Files (x86)\Reference Assemblies\Microsoft\Framework\.NETFramework\v4.5
		array<Point^>^ points;

		Solution();
		Solution(SOLUTION* sln);
	};

	public ref class PekoEngineNet
	{
	public:

		PekoEngineNet();
		~PekoEngineNet();
		int Initialize();

		Solution^ GetSolution(double scale);
		void Start();
		void Stop();
		void Reset();

	private:
		PekoEngine* m_pEngine;

	};
}
