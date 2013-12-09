clear

ys0=read("playstop2.dat",-1,1)
ys1=read("playstop_fixed.dat",-1,1)

sz0=size(ys0)
sz1=size(ys1)

xs0=[1:15:sz0(1,1)*15]'
xs1=[1:1:sz1(1,1)]'

xlabel("time(sec)")
ylabel("virtual bytes(M byte)")
plot2d(xs0,ys0./(10^6),color("red"))
plot2d(xs1,ys1./(10^6),color("blue"))
