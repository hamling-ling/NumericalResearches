clear;

// sampling num
samplenum=5000
// number of repetition
repeat=100;

// coin toss
R=grand(samplenum,repeat,'uin',0,1);
Avgs=mean(R,'c');
histplot([0:0.01:1],Avgs)

avg=1/2;
s=sqrt((1/4)/repeat);
x=[0:0.01:1];
plot(x,(1/(s*sqrt(2*%pi)))*exp(-((avg-x).^2)./(2*s^2)));

