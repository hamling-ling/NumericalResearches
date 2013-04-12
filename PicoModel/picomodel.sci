// parameters
ka=0.01
kl=1;
THETA=%pi/2
r=1
I=1
kd=0.3

// initial conditions
theta0=%pi
w0=0

clear model_eq
function xdot=model_eq(t,x)
    w=x(1)
    theta=x(2)
    xdot=zeros(2,1)
    xdot(1) = (- ka * theta + 4 * r^2 * kl * cos((theta+THETA)/2) * cos(2*THETA+theta) * sin(theta))/I //- kd * w
    xdot(2) = w
endfunction

ts=0:0.1:20;
sln=ode([w0;theta0], 0, ts, model_eq);

plot2d(ts,(sln(2,:)+THETA)/%pi)
