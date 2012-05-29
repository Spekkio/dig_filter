#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "complex.h"
#include "fft.h"

int main()
{
  #define SECONDS 1.0
  #define SAMPLES 1000

  #define FREQ 2
  #define FREQ2 14
  #define FFTs 1000

  float i;
  int a;
  c_vector x[SAMPLES],r;

  for(i=0.0,a=0;i<SECONDS;i+=(SECONDS/SAMPLES),a++)
    {
      x[a].f[REAL] = 0.5*sin(i*2*M_PI*FREQ)+0.8*sin(i*2*M_PI*FREQ2)+1.0*(((float)rand()/RAND_MAX)-0.5);
      x[a].f[IMAG] = 0;
    }

  /*X[k] = Sum[x[n]*exp(-I*2*Pi*(k*n)/N),{n,0,N-1}]*/
  /*fft(&result, input array x, number of array items N, Index k of result X[k])*/  
  for(a=0;a<=(SAMPLES*SECONDS/2.0);a++)
    {
      fftv(&r,x,SAMPLES,a);
      printf("%f\t%.52f\n",(a/(SECONDS)),i_absv(r)*(2.0/SAMPLES));
    }

  /*
  for(a=0;a<=FFTs;a++)
    {
      fftv(&r,x,SAMPLES,a);
      printf("%f\t%.52f\n",(float)a/SECONDS,i_absv(r)*(2.0/SAMPLES));
    }
  */  
  return 0;
}
