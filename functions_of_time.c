#include <math.h>
#include "functions_of_time.h"

/*
  LP Filter

       w^2
-------------------
s^2 + 2*d*w*s + w^2


                1/(C1*C2*R1*R2)
-------------------------------------------------
s^2 + s*(1/(C1*R1) + 1/(C1*R2)) + 1/(C1*C2*R1*R2)

Roots: 0<=d<1 roots are complex
s1 = -d*w-sqrt((d^2 - 1)*w^2)
s2 = -d*w+sqrt((d^2 - 1)*w^2)

  HP Filter

       s^2
-------------------
s^2 + 2*d*w*s + w^2


                     s^2
------------------------------------------------
s^2 + s(1/(C1*R2) + 1/(C2*R2)) + 1/(C1*C2*R1*R2)


*/

double lp_sallen_key_of_time(double R1, double R2, double C1, double C2, double t)
{
  return (-1 + exp((t*sqrt((-4*C1*R1*R2 + C2*pow(R1 + R2,2))/C2))/(C1*R1*R2)))/(exp((t*(R1 + R2 + sqrt((-4*C1*R1*R2 + C2*pow(R1 + R2,2))/C2)))/(2.*C1*R1*R2))* sqrt(C2*(-4*C1*R1*R2 + C2*pow(R1 + R2,2))));
}

double hp_sallen_key_of_time(double R1, double R2, double C1, double C2, double t)
{
  return (-(pow(C1,2)*R1) - 2*C1*C2*R1 -  pow(C2,2)*R1 + 2*C1*C2*R2 -  C1*sqrt(R1*(pow(C1 + C2,2)*R1 - 4*C1*C2*R2)) - exp((t*sqrt(pow(C1 + C2,2) - (4*C1*C2*R2)/R1))/(C1*C2*R2))*C1*sqrt(R1*(pow(C1 + C2,2)*R1 - 4*C1*C2*R2)) -	C2*sqrt(R1*(pow(C1 + C2,2)*R1 - 4*C1*C2*R2)) -  exp((t*sqrt(pow(C1 + C2,2) - (4*C1*C2*R2)/R1))/(C1*C2*R2))*C2*sqrt(R1*(pow(C1 + C2,2)*R1 - 4*C1*C2*R2)) +  exp((t*sqrt(pow(C1 + C2,2) - (4*C1*C2*R2)/R1))/(C1*C2*R2))*(pow(C1 + C2,2)*R1 - 2*C1*C2*R2))/(2*exp((t*(C1 + C2 + sqrt(pow(C1 + C2,2) - (4*C1*C2*R2)/R1)))/(2*C1*C2*R2))*C1*C2*R2*sqrt(R1*(pow(C1 + C2,2)*R1 - 4*C1*C2*R2)));
}
