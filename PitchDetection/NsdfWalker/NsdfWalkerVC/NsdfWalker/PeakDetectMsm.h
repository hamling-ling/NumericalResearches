#pragma once

#include <iostream>
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>

namespace osakanaengine {
	namespace msm = boost::msm;
	namespace msmf = boost::msm::front;
	namespace mpl = boost::mpl;

	// ----- Events
	struct PosCross  {};
	struct NegCross  {};
	struct NomlData  {};
	struct EndOfData {};

	// ----- State machine
	struct Sm1_ : msmf::state_machine_def<Sm1_>
	{
		// callback
		boost::function<void(void)> _bellStartCallback;
		boost::function<void(void)> _bellFinishCallback;

		// States
		struct SmState : msmf::state <>
		{
		};

		struct SearchingBell : SmState
		{
		};

		struct WalkingOnBell : SmState
		{
		};

		struct End : SmState
		{
		};

		// Set initial state
		typedef SearchingBell initial_state;

		// Actions
		struct BellStarted {

			template <class Event, class Fsm, class SourceState, class TargetState>
			void operator()(Event const&, Fsm& fsm, SourceState&, TargetState&) const
			{
				Sm1* sm1 = &fsm;
				if (sm1->_bellStartCallback) {
					sm1->_bellStartCallback();
				}
			}
		};

		struct BellFinished {
			template <class Event, class Fsm, class SourceState, class TargetState>
			void operator()(Event const&, Fsm& fsm, SourceState&, TargetState&) const
			{
				Sm1* sm1 = &fsm;
				if (sm1->_bellFinishCallback) {
					sm1->_bellFinishCallback();
				}
			}
		};

		// Transition table
		struct transition_table : mpl::vector<
			//          Start          Event      Next           Action        Guard
			msmf::Row < SearchingBell, PosCross,  WalkingOnBell, BellStarted,  msmf::none >,
			msmf::Row < SearchingBell, NegCross,  SearchingBell, msmf::none,   msmf::none >,
			msmf::Row < SearchingBell, NomlData,  SearchingBell, msmf::none,   msmf::none >,
			msmf::Row < SearchingBell, EndOfData, End,           msmf::none,   msmf::none >,

			msmf::Row < WalkingOnBell, PosCross,  WalkingOnBell, msmf::none,   msmf::none >,
			msmf::Row < WalkingOnBell, NegCross,  SearchingBell, BellFinished, msmf::none >,
			msmf::Row < WalkingOnBell, NomlData,  WalkingOnBell, msmf::none,   msmf::none >,
			msmf::Row < WalkingOnBell, EndOfData, End,           BellFinished, msmf::none >
		> {};

		// ----- State IDs
		typedef enum _MetaStateId {
			kSearchingBellStateId = 0,
			kWalkingOnBellStateId = 1,
			kEndStateId = 2
		} MetaStateId;
	};

	// Pick a back-end
	typedef msm::back::state_machine<Sm1_> Sm1;
}
