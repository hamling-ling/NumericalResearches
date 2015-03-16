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
// create freq-axis
fs = [0:sampleNum-1] * sampleFreq/sampleNum;
// data number for fft
N = sampleNum;
// fft
f_fft = fft(x);
power = f_fft.*conj(f_fft);
// correlation by fft
r=ifft(power);
taus=[0:N-1] * 1/sampleFreq;
// correlation by hand
M=N/2;
r2=zeros(1,M);
taus2=[0:M-1] * 1/sampleFreq;
for m=1:M+1
    for n=1:M-m+1
        r2(m)=r2(m)+x(n)*x(n+m-1);
    end;
end;

subplot(211);
plot2d(ts,x);
title = sprintf("A %dHz wave is sampled with sampling rate=%dHz",waveFreq,sampleFreq);
xtitle(title,"time (sec)","arbitral");

subplot(212);
plot(taus(1:M),r(1:M),taus2,r2);
xtitle("autocorrelation computed by two different way", "tau(s)", "auto correlation");
legend(["fft" "straight"], 1, "ur");
