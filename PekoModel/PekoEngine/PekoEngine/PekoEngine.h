#pragma once

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
		void Reset(MODELFLOAT newTheta, MODELFLOAT newOmega);
		void SetCallback(EngCallbackFunc callback, void* funcOwner);
		bool IsRunning();
		SOLUTION* GetSolution(SOLUTION* sln);

		// debug
		void CallMeBack();

	private :

		PekoModel*		m_pModel;
		pthread_mutex_t m_modelMutex;
		pthread_t		m_thread;
		EngCallbackFunc	m_pCallbackFunc;
		void*			m_pCallbackFuncOwner;
		bool			m_stopProc;
		bool			m_isProcRunning;

		static void*	EngineProc(void* arg);
		void			EngineLoop();
	};
}
