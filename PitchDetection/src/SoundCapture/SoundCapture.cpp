#include "SoundCapture.h"
#include <al.h>
#include <alc.h>
#include <iostream>// debug

using namespace std;

SoundCapture::SoundCapture(int sampleRate, int sampleNum)
: _sampleRate(sampleRate), _sampleNum(sampleNum), _sampleBuf(NULL), _selectedDeviceIndex(-1)
{
}

SoundCapture::~SoundCapture()
{
	delete(_sampleBuf);
}

bool SoundCapture::Initialize(SoundCaptureCallback_t callback)
{
	_callback = callback;
	_sampleBuf = new int16_t[_sampleNum];

	return true;
}

SoundCaptureError Start()
{
	return SoundCaptureErrorNoError;
}

SoundCaptureError Stop()
{
	return SoundCaptureErrorNoError;
}

std::vector<std::string> SoundCapture::GetDevices()
{
	std::vector<std::string> devices;
	return devices;
}

SoundCaptureError SoundCapture::SelectDevice(int index)
{
	return SoundCaptureErrorNoError;
}

void SoundCapture::CaptureLoop()
{
	ALCdevice *dev[2];
	ALCcontext *ctx;
	ALuint source, buffers[3];
	char data[5000];
	ALuint buf;
	ALint val;

	float ttotal;
	unsigned int ccount;
	long int count;
	count = 0;

	dev[0] = alcOpenDevice(NULL);
	ctx = alcCreateContext(dev[0], NULL);
	alcMakeContextCurrent(ctx);

	alGenSources(1, &source);
	alGenBuffers(3, buffers);

	/* Setup some initial silent data to play out of the source */
	alBufferData(buffers[0], AL_FORMAT_MONO16, data, sizeof(data), 22050);
	alBufferData(buffers[1], AL_FORMAT_MONO16, data, sizeof(data), 22050);
	alBufferData(buffers[2], AL_FORMAT_MONO16, data, sizeof(data), 22050);
	alSourceQueueBuffers(source, 3, buffers);

	/* If you don't need 3D spatialization, this should help processing time */
	alDistanceModel(AL_NONE);

	dev[1] = alcCaptureOpenDevice(NULL, 22050, AL_FORMAT_MONO16, sizeof(data) / 2); //22050 mean 22.050 samples per     second. or 44100 for 44.1 per second.

	/* Start playback and capture, and enter the audio loop */
	alSourcePlay(source);
	alcCaptureStart(dev[1]);    //starts ring buffer

	while (1)
	{
		/* Check if any queued buffers are finished */
		alGetSourcei(source, AL_BUFFERS_PROCESSED, &val);
		if (val <= 0)
			continue;

		/* Check how much audio data has been captured (note that 'val' is the
		* number of frames, not bytes) */
		alcGetIntegerv(dev[1], ALC_CAPTURE_SAMPLES, 1, &val);

		/* Read the captured audio */
		alcCaptureSamples(dev[1], data, val);


		//***** Process/filter captured data here *****//


		count = count + 1;
		if (count >= 330){
			break;
		}

		for (int ii = 0; ii<val; ++ii) {
			data[ii] *= 2.0; // Make it quieter
		}
		//***** end Process/filter captured data here *****//

		/* Pop the oldest finished buffer, fill it with the new capture data,
		then re-queue it to play on the source */
		alSourceUnqueueBuffers(source, 1, &buf);
		alBufferData(buf, AL_FORMAT_MONO16, data, val * 2 /* bytes here, not
														  frames */, 22050);
		alSourceQueueBuffers(source, 1, &buf);

		/* Make sure the source is still playing */
		alGetSourcei(source, AL_SOURCE_STATE, &val);

		if (val != AL_PLAYING)
		{
			alSourcePlay(source);
		}
	}

	cout << "fgggggggg\n";


	/* Shutdown and cleanup */
	alcCaptureStop(dev[1]);
	alcCaptureCloseDevice(dev[1]);

	alSourceStop(source);
	alDeleteSources(1, &source);
	alDeleteBuffers(3, buffers);
	alDeleteBuffers(1, &buf);

	alcMakeContextCurrent(NULL);
	alcDestroyContext(ctx);
	alcCloseDevice(dev[0]);
}