clc
clear all

// plot generic version of solution
exec 'StaticBernoulliBeamGeneric.sci'

// compute c1,c2 w/o using matrix
// y0dot=-y1dot and they are const
// and y0=y1=0, c1-c4 are more simpler
c1=w/2
c2=-w/12-2*y0dot
c3=y0dot
c4=0

// plot
simulate();

