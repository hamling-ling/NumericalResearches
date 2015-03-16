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
ts = [0:sampleNum-1] * 1/sampleFreq;
// create sin wave
x=sin(2 * %pi * waveFreq * ts);
x(sampleNum/2+1:sampleNum)=zeros(1,sampleNum/2);
// data number of data for fft
N = sampleNum;
// create freq-axis
fs = [0:sampleNum-1] * sampleFreq/sampleNum;
// fft
f_fft = fft(x);
power = f_fft.*conj(f_fft);
// correlation
r=N*ifft(power);
taus=[0:sampleNum-1] * 1/sampleFreq;

subplot(221);
plot2d(ts,x);
title = sprintf("A %dHz wave is sampled with sampling rate=%dHz",waveFreq,sampleFreq);
xtitle(title,"time (sec)","arbitral");

subplot(222);
plot2d("nl",fs,power);
xtitle("powerspectrum", "frequency(Hz)", "arbitral");

subplot(223);
plot2d(taus,r);
xtitle("autocorrelation by fft", "tau(s)", "arbitral");
