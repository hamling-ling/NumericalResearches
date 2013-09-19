// これは メイン DLL ファイルです。

#include "stdafx.h"

#include "PekoEngineNet.h"


namespace PekoEngineNet {

	Solution::Solution()
	{
	}

	Solution::Solution(SOLUTION *pSln)
	{
		theta	= pSln->theta.z;
		omega	= pSln->omega.z;
		t		= pSln->t;
		points = gcnew array<Point^>(MODEL_POINTS_LEN);
		for(int i = 0; i < MODEL_POINTS_LEN; i++)
		{
			Point^ p = gcnew Point();
			p->X =pSln->points[i].x;
			p->Y =pSln->points[i].y;

			points[i]=p;
		}
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

	Solution^ PekoEngineNet::GetSolution(double scale)
	{
		SOLUTION natSln;
		m_pEngine->GetSolution(&natSln, scale);

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

	void PekoEngineNet::Reset()
	{
		m_pEngine->Reset();
	}
}
