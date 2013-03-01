function y = fun2fit(x, c)
  y =  c(1)*x  + c(2);
 endfunction 
 
function e = myerror(c, x, y)
  e = fun2fit(x, c) - y;
endfunction 

xy=read("test.txt",-1,2);
xfull=xy(:,1)
yfull=xy(:,2)
x=xfull(300:length(xfull))
y=yfull(300:length(yfull))

tgty = zeros(length(y),1)
tgty = tgty + 44444

c0 = [1, 0]
[f, copt] = leastsq(list(myerror, x, y), c0) 
yopt0 = fun2fit(x, copt)

plot2d(x, [y yopt0])
