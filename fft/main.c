#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "complex.h"
#include "fft.h"

int main()
{
  float i;
  int a;
  complex x[100],r;


  for(i=0.0,a=0;i<1.0;i+=(1.0/100),a++)
    {
      x[a].real = sin(i*2*M_PI*120.0);
      x[a].imag = 0;
    }

  /*X[k] = Sum[x[n]*exp(-I*2*Pi*(k*n)/N),{n,0,N-1}]*/
  /*fft(&result, input array x, number of array items N, Index k of result X[k])*/
  for(a=0;a<100;a++)
    {
      fft(&r,x,100,a);
      printf("%+.30f%+.30fi -> %f\n",r.real,r.imag,i_abs(r));
    }

  return 0;
}
