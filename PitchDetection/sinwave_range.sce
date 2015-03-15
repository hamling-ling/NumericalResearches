funcprot(0);
clear all;

//////////////////////////////////////////////////////////////////////
// parameters
//////////////////////////////////////////////////////////////////////
sampleNum = 4096;   // sample number
sampleFreq = 44100; // sampling frequency
baseWaveFreq = 27.5;// base wave frequency

//////////////////////////////////////////////////////////////////////
// main
//////////////////////////////////////////////////////////////////////
// create time-axis
ts = [0:sampleNum-1] * 1/sampleFreq;
// create sin wave of frequency 
// 27.5, 55, 110, 220, 440, 880, 1760, 3520 Hz
powNum = 4;
pows=[0:powNum-1]';
fs=baseWaveFreq*(2^pows);
waves = sin(2 * %pi * fs * ts);

// plot
for i=1:powNum,
    subplot(int(powNum/2)*100+20+i)
    plot2d(ts,waves(i,:));
    legendtext = sprintf("%f Hz",fs(i));
    legends(legendtext,1,"ur");
end

