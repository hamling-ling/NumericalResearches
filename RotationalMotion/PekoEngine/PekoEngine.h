#pragma once

#include <vector>
#include <pthread.h>
#include "PekoModel.h"
#define SAFE_DELETE(p)  { delete p; p=NULL; }

using namespace std;
using namespace pekomodel;


namespace pekoengine {

	typedef struct ENGINEEVENTARG
	{
		SOLUTION sln;
	} EngineEventArg;

	typedef void (__stdcall *EngCallbackFunc)(void*, EngineEventArg);

	class PekoEngine
	{
	public :

		PekoEngine();
		~PekoEngine();

		int Initialize();
		void Start();
		void Stop();
		void Reset();
		bool IsRunning();
		
		SOLUTION* GetSolution(SOLUTION* sln, double scale);

	private :

		PekoModel*		m_pModel;
		pthread_mutex_t m_modelMutex;
		pthread_t		m_thread;
		bool			m_stopProc;
		bool			m_isProcRunning;

		static void*	EngineProc(void* arg);
		void			EngineLoop();
	};
}
