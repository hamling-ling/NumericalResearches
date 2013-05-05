clc
clear all

// scilab script compute static Bernoulli Beam
// gamma*d^4 y/dx^r=W(x)
// when w(x) is uniformly distributed the is
// gamma y(x)=-W*(x^4)/24+C1*(x^3)/6+C2*(x^2)/2+C3*x+C4
// in this program, we eliminates gamma by replacing
// w=W/gamma, cn=Cn/gamma

// parameters
w=100   // w

// boundary conditions
y0=0    // y(0)
y1=0    // y(1)
y0dot=3 // d/dx y(0)
y1dot=-y0dot // d/dx y(1)

// computing constants c1-c4
A=[ 1/6 1/2 1   1;
    0   0   1   1;
    1/2 1   1   1
    0   0   0   1]

b=[w/24+y1  y0dot   y1dot+w/6   0]'

x=inv(A)*b

c1=x(1)
c2=x(2)
c3=x(3)
c4=x(4)

function y=f(x)
    y = -w*(x^4)/24 + c1*(x^3)/6 + c2*(x^2)/2 + c3*x + c4
endfunction

function simulate()
    xs=0:0.01:1;
    ys=f(xs);
    plot2d(xs,ys)
endfunction

simulate();

title('Static Bernoulli Beam Simulation');
xlabel('$x$');
ylabel('$y(x)$');
    
