funcprot(0);
clear all;

//////////////////////////////////////////////////////////////////////
// parameters
//////////////////////////////////////////////////////////////////////
sampleNum = 1024;   // sample number
sampleFreq = 44100; // sampling frequency
waveFreq = 440;     // wave frequency

//////////////////////////////////////////////////////////////////////
// main
//////////////////////////////////////////////////////////////////////
// create time-axis
ts = [0:sampleNum] * 1/sampleFreq;
// create sin wave
f=sin(2 * %pi * waveFreq * ts);
// data number of data for fft
N = sampleNum/2;
// create freq-axis
fs = [0:sampleNum] * sampleFreq/sampleNum;
// fft
f_fft = fft(f);
power = f_fft.*conj(f_fft);

subplot(211);
plot2d(ts,f);
title = sprintf("A %dHz wave is sampled with sampling rate=%dHz",waveFreq,sampleFreq);
xtitle(title,"time (sec)","arbitral");

subplot(212);
plot2d("nl",fs(1:N),power(1:N));

[maxPower,maxIndex] = max(abs(power(1:N)));
maxFreq=fs(maxIndex);
printf("max frequency range=%f~%f\n",maxFreq, maxFreq + sampleFreq/sampleNum);
