// これは メイン DLL ファイルです。

#include "stdafx.h"

#include "PekoEngineNet.h"


namespace PekoEngineNet {

	Solution::Solution()
	{
	}

	Solution::Solution(SOLUTION *pSln)
	{
		theta = pSln->theta;
		omega = pSln->omega;
	}

	PekoEngineNet::PekoEngineNet()
		: m_pEngine(NULL)
	{
		m_pEngine = new PekoEngine();
	}

	PekoEngineNet::~PekoEngineNet()
	{
		Stop();
		delete m_pEngine;
	}

	int PekoEngineNet::Initialize()
	{
		return m_pEngine->Initialize();
	}

	Solution^ PekoEngineNet::GetSolution()
	{
		SOLUTION natSln;
		m_pEngine->GetSolution(&natSln);

		Solution^ clrSln = gcnew Solution(&natSln);
		return clrSln;
	}

	void PekoEngineNet::Start()
	{
		m_pEngine->Start();
	}

	void PekoEngineNet::Stop()
	{
		m_pEngine->Stop();
	}

	void PekoEngineNet::Reset(float newTheta, float newOmega)
	{
		m_pEngine->Reset(newTheta, newOmega);
	}
}
