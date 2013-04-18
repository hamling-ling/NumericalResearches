#include "stdafx.h"
#include "PekoEngine.h"

#include <exception>

#ifdef WIN32
#include <Windows.h>
#define MILSLEEP(ms)	Sleep((DWORD)(ms))
#else
#define MILSLEEP(ms)	usleep(1000*(ms))
#endif

using namespace std;
using namespace pekomodel;

namespace pekoengine {

	PekoEngine::PekoEngine()
		:	m_pModel(NULL), m_isProcRunning(false), m_stopProc(false)
	{
		m_pModel = new PekoModel();
		m_pCallbackFunc = NULL;
		m_pCallbackFuncOwner = NULL;
	}

	PekoEngine::~PekoEngine()
	{
		Stop();
		pthread_mutex_destroy(&m_modelMutex);
		delete m_pModel;
	}

	int PekoEngine::Initialize()
	{
		pthread_mutex_init(&m_modelMutex,NULL);
		return 0;
	}

	void PekoEngine::Start()
	{
		Stop();

		m_stopProc = false;
		pthread_create(&m_thread, NULL, EngineProc, this);
	}

	void PekoEngine::Stop()
	{
		if(!m_isProcRunning)
			return;

		m_stopProc = true;
		pthread_join(m_thread, NULL);
	}

	void PekoEngine::Reset(MODELFLOAT newTheta, MODELFLOAT newOmega)
	{
		Stop();

		pthread_mutex_lock(&m_modelMutex);
		m_pModel->Reset(newTheta, newOmega);
		pthread_mutex_unlock(&m_modelMutex);
	}

	void PekoEngine::SetCallback(EngCallbackFunc callback, void* funcOwner)
	{
		m_pCallbackFunc = callback;
		m_pCallbackFuncOwner = funcOwner;
	}

	bool PekoEngine::IsRunning()
	{
		return m_isProcRunning;
	}

	SOLUTION* PekoEngine::GetSolution(SOLUTION* sln)
	{
		pthread_mutex_lock(&m_modelMutex);
		m_pModel->GetSolution(sln);
		pthread_mutex_unlock(&m_modelMutex);

		return sln;
	}

	void* PekoEngine::EngineProc(void* arg)
	{
		reinterpret_cast<PekoEngine*>(arg)->EngineLoop();
		pthread_exit(NULL);
		return NULL;
	}

	void PekoEngine::EngineLoop()
	{
		m_isProcRunning = true;

		while(!m_stopProc) {

			pthread_mutex_lock(&m_modelMutex);
			m_pModel->GetNext();

			// Notify
			if(m_pCallbackFunc && m_pCallbackFuncOwner != NULL) {
				EngineEventArg arg;

				m_pModel->GetSolution(&arg.sln);
				pthread_mutex_unlock(&m_modelMutex);

				if(m_stopProc)
					break;

				m_pCallbackFunc(m_pCallbackFuncOwner, arg);
			}
			else {
				pthread_mutex_unlock(&m_modelMutex);
			}

			MILSLEEP(MODEL_DELTA_T * 1000.0);
		}

		m_isProcRunning = false;
	}
}