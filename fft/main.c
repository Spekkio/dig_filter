#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "complex.h"
#include "fft.h"

int main()
{
  #define SECONDS 1.0
  #define SAMPLES 1000
  #define FREQ 124
  
  float i;
  int a;
  complex x[SAMPLES],r;

  for(i=0.0,a=0;i<SECONDS;i+=(SECONDS/SAMPLES),a++)
    {
      x[a].real = sin(i*2*M_PI*FREQ)+(float)rand()/RAND_MAX;
      x[a].imag = 0;
    }

  /*X[k] = Sum[x[n]*exp(-I*2*Pi*(k*n)/N),{n,0,N-1}]*/
  /*fft(&result, input array x, number of array items N, Index k of result X[k])*/
  for(a=0;a<(SAMPLES*SECONDS/2);a++)
    {
      fft(&r,x,SAMPLES,a);
      /*printf("%+.30f%+.30fi -> %f\n",r.real,r.imag,i_abs(r));*/
      printf("%f\t%.52f\n",a/SECONDS,i_abs(r)*(2.0/SAMPLES));
    }

  return 0;
}
