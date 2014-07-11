clear;

// sampling num
samplenum=1000
// number of repetition
repeat=100;

R=grand(samplenum,repeat,'uin',-1,1);
// avarage of repetition
X=sum(R,'c');

//plot2d(X);

//param=[-samplenum:samplenum];
//param=10;//[-samplenum:5:samplenum]/4;
param=[-50:1:50];
histplot(param,X)

avg=0
s=sqrt(1/repeat);
x=[-50:0.05:50];
//plot(x,(1/(s*sqrt(2*%pi)))*exp(-((avg-x).^2)/(2*s^2)));

plot(x,(1/sqrt(2*%pi*repeat))*exp(-(x.^2)./(2*repeat)));
