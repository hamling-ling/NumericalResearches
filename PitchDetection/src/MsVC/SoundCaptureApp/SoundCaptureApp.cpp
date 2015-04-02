// SoundCaptureApp.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "SoundCapture.h"
#include <iostream>
#include <string>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	SoundCapture cap(8000, 1024);
	cap.Start();

	string input;
	cin >> input;

	cap.Stop();

	return 0;
}

