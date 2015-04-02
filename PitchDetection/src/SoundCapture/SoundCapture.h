#pragma once

#include <vector>
#include <cstdint>
#include <functional>
#include <thread>
#include <mutex>

typedef enum SoundCaptureError {
	SoundCaptureErrorNoError,
	SoundCaptureErrorAlreadyRunning,
	SoundCaptureErrorNoDevice,
	SoundCaptureErrorInternal,
};

class SoundCapture;
typedef std::function < void(SoundCapture*, void*)> SoundCaptureCallback_t;

class SoundCapture
{
public:
	SoundCapture(int sampleRate, int sampleNum);
	virtual ~SoundCapture();

	bool Initialize(SoundCaptureCallback_t callback);
	SoundCaptureError Start();
	SoundCaptureError Stop();
	std::vector<std::string> GetDevices();
	SoundCaptureError SelectDevice(int index);

private:
	const int _sampleRate;
	const int _sampleNum;
	int16_t* _sampleBuf;
	int _selectedDeviceIndex;
	std::thread _thread;
	bool _isRunning;
	bool _stopRunning;
	std::recursive_mutex _mutex;

	SoundCaptureCallback_t _callback;
	void CaptureLoop();
};

