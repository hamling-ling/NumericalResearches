#include "stdafx.h"
#include "NsdfWalker.h"
#include <cassert>
#include "NsdfPeakDetectMachine.h"

namespace osakanaengine {

	NsdfWalker::NsdfWalker(uint32_t maxDataNum)
		: _maxDataNum(maxDataNum), _currentIndex(0)
	{
		assert(maxDataNum != 0);

		_keyMaxs.reserve(kReservedBellNumber);
		memset(&_localKeyMax, 0, sizeof(_localKeyMax));
		memset(&_globalKeyMax, 0, sizeof(_globalKeyMax));
		memset(&_lastInput, 0, sizeof(_lastInput));

		_sm = std::make_shared<NsdfPeakDetectMachine>();
		_sm->SetBellStartedHandler(boost::bind(&NsdfWalker::BellStarted, this, _1));
		_sm->SetBellFinishHandler(boost::bind(&NsdfWalker::BellFinished, this, _1));
	}

	NsdfWalker::~NsdfWalker()
	{
	}

	void NsdfWalker::Input(double x)
	{
		if (_sm->IsFinished()) {
			std::cerr << "finished state" << std::endl;
			return;
		}

		std::cout << "x[" << _currentIndex << "]=" << x << std::endl;

		if (_sm->IsWalkingOnBell()) {
			// update local key max
			if (_localKeyMax.value < x) {
				_localKeyMax.value = x;
				_localKeyMax.index = _currentIndex;
			}
			// update global key max
			if (_globalKeyMax.value < x) {
				_globalKeyMax.value = x;
				_globalKeyMax.index = _currentIndex;
			}
		}

		if (0 <= _lastInput.value && x < 0) {
			_sm->NegativeCross();
		}
		else if (_lastInput.value < 0 && 0 <= x) {
			_sm->PositiveCross();
		}
		else {
			_sm->NormalDataInput();
		}

		_lastInput.value = x;
		_lastInput.index = _currentIndex;

		_currentIndex++;

		if (_maxDataNum <= _currentIndex) {
			_sm->EndOfDataInput();
		}
	}

	void NsdfWalker::GetKeyMaximums(std::vector<NsdfPoint>& out)
	{
		for (auto keyMax : _keyMaxs) {
			if (_globalKeyMax.value * kThreshold <= keyMax.value) {
				out.push_back(keyMax);
			}
		}
	}

	void NsdfWalker::BellStarted(NsdfPeakDetectMachine* pdm)
	{
		// nothing to do
		std::cout << "bell started" << std::endl;
	}

	void NsdfWalker::BellFinished(NsdfPeakDetectMachine* pdm)
	{
		_keyMaxs.push_back(_localKeyMax);

		std::cout << "bell finished maximum(value,index)=("
			<< _localKeyMax.index << ", " << _localKeyMax.value << ")" << std::endl;

		// reset local key maximum
		_localKeyMax.index = 0;
		_localKeyMax.value = 0;
	}

}
