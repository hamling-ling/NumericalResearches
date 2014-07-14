clear;

// sampling num
samplenum=1000
// number of repetition
repeat=100;

// coin toss
R=grand(samplenum,repeat,'uin',0,1);
sums=sum(R,'c');

histplot([0:1:samplenum],sums)

n=repeat;
p=1/2;

avg=n*p;
s=sqrt(n*p*(1-p))
x=[0:0.1:samplenum];
plot(x,(1/(s*sqrt(2*%pi)))*exp(-((avg-x).^2)./(2*s^2)));
