#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "complex.h"
#include "fft.h"

int main()
{
  /*
  #define SAMPLE_TIME 1.0
  #define S_TIME 0.1
  #define S_FREQ (1.0/S_TIME)

  #define MAX_FREQ 15
  #define SAMPLES ((unsigned long int)(SAMPLE_TIME*S_TIME))
  #define SECONDS (S_TIME/SAMPLES)
  */

  #define SAMPLES 1000
  #define SECONDS 1.0
  #define S_TIME (SECONDS/SAMPLES)
  #define S_FREQ (1.0/S_TIME)
  
  #define FREQ 2
  #define FREQ2 17
  #define FREQ3 401
  #define FFTs 1000

  float i;
  int a;
  c_vector x[SAMPLES],r;

  for(i=0.0,a=0;i<SECONDS;i+=S_TIME,a++)
    {
      x[a].f[REAL] = 0.5*sin(i*2*M_PI*FREQ)+0.8*sin(i*2*M_PI*FREQ2)+0.6*sin(i*2*M_PI*FREQ3)+5.0*(((float)rand()/RAND_MAX)-0.5);
      x[a].f[IMAG] = 0;
      /*
      printf("%.52f\t%.52f\n",i,x[a].f[REAL]);
      */
    }

  /*X[k] = Sum[x[n]*exp(-I*2*Pi*(k*n)/N),{n,0,N-1}]*/
  /*fft(&result, input array x, number of array items N, Index k of result X[k])*/  
  
  for(a=0;a<=(SAMPLES/2.0);a++)
    {
      fftv(&r,x,SAMPLES,a);

      printf("%f\t%.52f\n",a/SECONDS,i_absv(r)*(2.0/SAMPLES));

    }

  return 0;
}
