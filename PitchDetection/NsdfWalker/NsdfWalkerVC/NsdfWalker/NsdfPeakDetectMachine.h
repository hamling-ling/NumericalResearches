#pragma once

#include <boost/bind/bind.hpp>
#include <boost/function.hpp>

#include "PeakDetectMsm.h"

namespace osakanaengine {
	class NsdfPeakDetectMachine;
	typedef boost::function<void(NsdfPeakDetectMachine*)> bellStartedCallback_t;
	typedef boost::function<void(NsdfPeakDetectMachine*)> bellFinishedCallback_t;

	/**
	 *	Wrapping meta state machine
	 */
	class NsdfPeakDetectMachine
	{
	public:
		NsdfPeakDetectMachine();
		virtual ~NsdfPeakDetectMachine();
		void SetBellStartedHandler(bellStartedCallback_t callback);
		void SetBellFinishHandler(bellFinishedCallback_t callback);
		void PositiveCross();
		void NegativeCross();
		void NormalDataInput();
		void EndOfDataInput();
		bool IsFinished();
		bool IsWalkingOnBell();
	private:
		bellStartedCallback_t _bellStartedCallback;
		bellFinishedCallback_t _bellFinishedCallback;
		Sm1 _sm;
		void BellStarted();
		void BellFinished();
	};

}
