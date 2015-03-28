#include "stdafx.h"
#include "NsdfPeakDetectMachine.h"

namespace osakanaengine {

	NsdfPeakDetectMachine::NsdfPeakDetectMachine()
	{
		_sm._bellStartCallback = boost::bind(&NsdfPeakDetectMachine::BellStarted, this);
		_sm._bellFinishCallback = boost::bind(&NsdfPeakDetectMachine::BellFinished, this);
		_sm.start();
	}

	NsdfPeakDetectMachine::~NsdfPeakDetectMachine()
	{
	}

	void NsdfPeakDetectMachine::SetBellStartedHandler(bellStartedCallback_t callback)
	{
		_bellStartedCallback = callback;
	}

	void NsdfPeakDetectMachine::SetBellFinishHandler(bellFinishedCallback_t callback)
	{
		_bellFinishedCallback = callback;
	}

	void NsdfPeakDetectMachine::PositiveCross()
	{
		_sm.process_event(PosCross());
	}

	void NsdfPeakDetectMachine::NegativeCross()
	{
		_sm.process_event(NegCross());
	}

	void NsdfPeakDetectMachine::NormalDataInput()
	{
		_sm.process_event(NomlData());
	}

	bool NsdfPeakDetectMachine::IsFinished()
	{
		int currentState = _sm.current_state()[0];
		return (Sm1_::kEndStateId == currentState);
	}

	bool NsdfPeakDetectMachine::IsWalkingOnBell()
	{
		int currentState = _sm.current_state()[0];
		return (Sm1_::kWalkingOnBellStateId == currentState);
	}

	void NsdfPeakDetectMachine::EndOfDataInput()
	{
		_sm.process_event(EndOfData());
	}

	void NsdfPeakDetectMachine::BellStarted()
	{
		if (_bellStartedCallback) {
			_bellStartedCallback(this);
		}
	}

	void NsdfPeakDetectMachine::BellFinished()
	{
		if (_bellFinishedCallback) {
			_bellFinishedCallback(this);
		}
	}
}
