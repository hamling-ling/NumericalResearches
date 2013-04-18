// parameters
ka=7.0525   // tosional spring constant
kl=100;      // horizontal spring constant
kd=2.9      // decay const

THETA=%pi/2 // angle w/o spring
r=1         // radius
I=1         // moment of inertia

// initial conditions
theta0=%pi*(1.5/2)
w0=0

clear displacement

function x=displacement(angle_a,angle_b)
    x_a=(2*r*sin(angle_a/2))
    x_b=(2*r*sin(angle_b/2))
    x=x_b-x_a
endfunction

clear torque_l
function x=torque_l(angle_a,angle_b)
    displ = displacement(angle_a, angle_a + angle_b)
    Fl = kl * displ
    x = r * Fl * (-1) .* sin((%pi + angle_a + angle_b)/2)
endfunction

clear torque_a
function x=torque_a(angle)
    x = - ka * angle
endfunction

clear model_eq
function xdot=model_eq(t,x)
    w=x(1)
    theta=x(2)
    xdot=zeros(2,1)
    
    tau_l = torque_l(THETA, theta)
    tau_a = torque_a(theta)
    xdot(1) = (tau_a +  tau_l)/I - kd * w
    xdot(2) = w
endfunction

clear simulate
function simulate()
    ts=0:0.1:60;
    sln=ode([w0;theta0], 0, ts, model_eq);
    plot2d(ts,(sln(2,:)+THETA)/%pi)
endfunction

clear simulatemany
function simulatemany()
    theta0s=linspace(%pi*(1.4/2),%pi*(1.9/2),20)
    for theta0=theta0s
        ts=0:0.1:60;
        sln=ode([w0;theta0], 0, ts, model_eq);
        plot2d(ts,(sln(2,:)+THETA)/%pi)
    end
endfunction

//simulate();
simulatemany();

title('Peco Model Simulation');
xlabel('$Time[s])$');
ylabel('$\theta+\theta_0[rad]$');
    
