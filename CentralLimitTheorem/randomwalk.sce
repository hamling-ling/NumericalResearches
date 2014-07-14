clear;

// sampling num
samplenum=1000
// number of repetition
repeat=100;

R=grand(samplenum,repeat,'uin',0,1);
R=1-R*2;
// avarage of repetition
X=sum(R,'c');

//plot2d(X);

param=[-50:1:50];
histplot(param,X)

n=repeat;
p=1/2;

avg=0;
s=sqrt(n*p*(1-p))
x=[-50:0.05:50];
plot(x,(1/(s*sqrt(2*%pi)))*exp(-((avg-x).^2)/(2*s^2)));
