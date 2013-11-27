clear;

xs=read('out.dat',-1,1)
N=length(xs)

f=[0:N-1]'

F_xs=fft(xs)
Fi_xs=ifft(F_xs)

plot(f,xs, f,Fi_xs)

//plot2d("ll",f(2:N/2),F_xs(2:N/2).*F_xs(2:N/2))
