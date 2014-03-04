clear all

POINTS = 2

for n=0:49

    data=read(string(n)+".dat",-1,3)
    dataSize=size(data)
    dataLen=dataSize(:,1)

    x0=data(dataLen-POINTS+1,2)
    y0=data(dataLen-POINTS+1,3)

    indices=dataLen-POINTS+1:dataLen
    plot2d( data(indices,2)-x0,data(indices,3)-y0,2)

end
