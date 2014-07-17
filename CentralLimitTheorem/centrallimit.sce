clc;

// number of repetition
repeat=10;
// draw dice 10 times. and repeat it.
X=grand(1000,repeat,'uin',1,6);
// avarage of repetition
R=mean(X,'c');
// plot histgram
histplot([0:0.1:6],R);
title="Frequency distribution of dice face with " +string(repeat)+" roll(s)";
xtitle(title,"dice face","Frequency");

avg=3.5
s=sqrt(2.92/repeat);
x=[0:0.01:6];
plot(x,(1/(s*sqrt(2*%pi)))*exp(-((avg-x).^2)/(2*s^2)));
