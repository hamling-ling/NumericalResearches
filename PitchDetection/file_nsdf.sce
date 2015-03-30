funcprot(0);
clear all;

//////////////////////////////////////////////////////////////////////
// parameters
//////////////////////////////////////////////////////////////////////
sampleNum = 1024;   // sample number

infile='piano_A.wav';
[dat, info] = loadwave(infile);
sampleFreq = info(3);// sampling rate
//////////////////////////////////////////////////////////////////////
// main
//////////////////////////////////////////////////////////////////////
W=sampleNum;
// create time-axis
ts = [0:W-1] * 1/sampleFreq;
// create sin wave
x=dat(1:W);
x(W/2+1:W)=zeros(1,W/2);
// create freq-axis
fs = [0:W-1] * sampleFreq/W;
// fft
f_fft = fft(x);
power = f_fft.*conj(f_fft);
// correlation by fft
r=ifft(power);
taus=[0:W-1] * 1/sampleFreq;
// normalized square difference
w=W/2;// number of correlation time lag
x2=x.^2;
m=zeros(1,w);
for t=1:w
    for j=1:w-t+1
       m(t) = m(t) + x2(j) + x2(t+j-1);// square diff.
    end;
end;
nsdf=2*r(1:w)./m;

subplot(311);
plot2d(ts,x);
title = sprintf("%s wave with sampling rate=%dHz",infile,sampleFreq);
xtitle(title,"time (sec)","arbitral");

subplot(312);
plot2d(taus(1:w),r(1:w));
xtitle("autocorrelation", "tau(s)", "auto correlation");

subplot(313);
plot2d(taus(1:w),nsdf(1:w));
xtitle("normalized square difference", "tau(s)", "a.u.");

// file output
dir=pwd();
csvWrite(x(1:sampleNum)', "file_orig.csv");
csvWrite(nsdf(1:w)', "file_nsdf.csv");
