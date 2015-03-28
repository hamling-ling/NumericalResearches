#pragma once

#include <vector>
#include <cstdint>
#include <memory>

namespace osakanaengine {
	static const double kThreshold = 0.8;
	static const unsigned int kReservedBellNumber = 64;

	typedef struct _NsdfPoint {
		double value;
		uint32_t index;
		uint32_t padding;
	} NsdfPoint;

	class NsdfPeakDetectMachine;

	/**
	 * finding maximums between positive zero-crossing and negative zero-crossing
	 * of Normalized square difference curve.
	 */
	class NsdfWalker
	{
	public:
		/**
		 * ctor
		 */
		NsdfWalker(uint32_t maxDataNum);

		/**
		 * dtor
		 */
		virtual ~NsdfWalker();

		/**
		 * handles input
		 */
		void Input(double x);

		/**
		 * returns key maximum. key maximums smaller than
		 * kThreshold * maximum are filtered out.
		 */
		void GetKeyMaximums(std::vector<NsdfPoint>& out);

	private:
		const uint32_t _maxDataNum;
		uint32_t _currentIndex;
		NsdfPoint _lastInput;
		// collection of key maximum for each bell
		std::vector<NsdfPoint> _keyMaxs;
		// max of all bell
		NsdfPoint _globalKeyMax;
		// max of current bell
		NsdfPoint _localKeyMax;
		// state machine
		std::shared_ptr<NsdfPeakDetectMachine> _sm;
		// call back handler from state machine event
		void BellStarted(NsdfPeakDetectMachine* pdm);
		// call back handler from state machine event
		void BellFinished(NsdfPeakDetectMachine* pdm);
	};

}
