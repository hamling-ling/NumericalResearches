clc;

// number of repetition
repeat=1;
// draw dice 10 times. and repeat it.
X=grand(100,repeat,'uin',1,6);
// avarage of repetition
R=mean(X,'c');
// plot histgram
histplot([0:0.1:6],R);
title="Frequency distribution of dice face with " +string(repeat)+" roll(s)";
xtitle(title,"dice face","Frequency");
