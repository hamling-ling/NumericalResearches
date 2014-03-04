clear all

for n=0:49

    data=read(string(n)+".dat",-1,3)
    dataLen=size(data)

    x0=data(1,2)
    y0=data(1,3)
    plot2d(data(:,2)-x0, data(:,3)-y0, 2)

end
