// draw a 3D version of StaticBernoulliBeam

clc
clear all

function y=f(x,w,c1,c2,c3,c4)
    x=0.5+x
    y = -w*(x^4)/24 + c1*(x^3)/6 + c2*(x^2)/2 + c3*x + c4
endfunction

function simulate()

    xs=linspace(-0.5,0.5,32);
    ys=linspace(-0.5,0.5,32);
    zs=zeros(length(xs),length(ys))
    y0=0    // y(0)
    y1=0    // y(1)

    w=100+50*1
    y0dot=3-3.0*1
    c1=w/2
    c2=-w/12-2*y0dot
    c3=y0dot
    c4=0
    
    for i=1:length(ys)
        y=ys(i)
        for j=1:length(xs)
            x=xs(j)
            zs(j,i)=f(sqrt(x^2+y^2),w,c1,c2,c3,c4)
        end
    end

    plot3d(xs,ys,zs)
    
endfunction

// plot
simulate();

