// Boundary conditions
//y(0)=0
//y(1)=0

// Compute c1,c2 w/o using matrix. In Following conditions
// dy0/dt=-dy1/dt and y0=y1=0, c1-c4 can be simpler
// c1=w/2
// c2=-w/12-2*dy(0)/dt
// c3=dy(0)/dt
// c4=0

clc
clear all

function y=f(x)
    y = -w*(x^4)/24 + c1*(x^3)/6 + c2*(x^2)/2 + c3*x + c4
endfunction

function simulate()
    xs=0:0.01:1;
    
    y0=0    // y(0)
    y1=0    // y(1)
    
    for i=[0:20]
            // parameter
        w=100+i*0.1
        y0dot=3-3.3*i/20
        
        c1=w/2
        c2=-w/12-2*y0dot
        c3=y0dot
        c4=0
        ys=f(xs);
        plot2d(xs,ys)
    end

endfunction

// plot
simulate();

