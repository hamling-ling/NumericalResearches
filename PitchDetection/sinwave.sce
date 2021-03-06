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
ts = [0:sampleNum-1] * 1/sampleFreq;
f=sin(2 * %pi * waveFreq * ts);
plot2d(ts,f);
title = sprintf("A %dHz wave is sampled with sampling rate=%dHz",waveFreq,sampleFreq);
xtitle(title,"time (sec)","arbitral");
