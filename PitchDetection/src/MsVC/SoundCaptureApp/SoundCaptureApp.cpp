// SoundCaptureApp.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "SoundCapture.h"
#include "PitchDetector.h"
#include <iostream>
#include <string>

using namespace std;

struct AppData {
	PitchDetector* det;
	float* buf;
};

void SoundCapEvent(SoundCapture* sc, SoundCaptureNotification note)
{
	if(SoundCaptureNotificationTypeCaptured == note.type) {
		int level = sc->Level();
		if (level < 20) {
			return;
		}

		AppData* appData = static_cast<AppData*>(note.user);
		sc->GetBuffer(appData->buf);

		if (appData->det->Detect(appData->buf)) {
			PitchInfo pitch;
			appData->det->GetPiatch(pitch);

			cout << "level:" << level << ", pitch:" << pitch.noteStr << endl;
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	const int samplingRate = 22050;
	const int samplingSize = 1024;
	AppData appData;
	PitchDetector det(samplingRate, 1024);
	if (!det.Initialize()) {
		return 1;
	}

	SoundCapture cap(samplingRate, 1024);
	if (!cap.Initialize(&SoundCapEvent, static_cast<void*>(&appData))) {
		return 1;
	}

	appData.det = &det;
	appData.buf = new float[samplingSize];

	cap.Start();

	string input;
	cin >> input;

	cap.Stop();
	delete(appData.buf);

	return 0;
}

