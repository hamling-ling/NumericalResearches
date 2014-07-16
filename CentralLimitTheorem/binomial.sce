clear;

// sampling num
samplenum=50
// number of repetition
repeat=10000;

// coin toss
R=grand(samplenum,repeat,'uin',0,1);

scf(1);
sums=sum(R,'r');
histplot([0:1:samplenum],sums)

n=samplenum;
p=1/2;

avg=n*p;
s=sqrt(n*p*(1-p))
x=[0:0.1:samplenum];
plot(x,(1/(s*sqrt(2*%pi)))*exp(-((avg-x).^2)./(2*s^2)));

