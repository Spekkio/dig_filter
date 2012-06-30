#include <complex.h>
#include <math.h>
#include "fft.h"

float complex * fft(float complex * r, const float complex * x, const unsigned long int N, const unsigned long int k)
{
  unsigned long int n;
  float complex ret;

  ret = 0 + _Complex_I*0;

  for(n=0;n<=(N-1);n++)
    {
      ret+=(cexp(0.0 - _Complex_I*(2*M_PI)*((k*n)/((float)N))) * x[n]);
    }
  *r=ret;
  return r;
}

float complex * ifft(float complex * r, const float complex * x, const unsigned long int N, const unsigned long int k)
{
  unsigned long int n;
  float complex ret;

  ret = 0 + _Complex_I*0;

  for(n=0;n<=(N-1);n++)
    {
      ret+=x[n]*cexp(0.0 + _Complex_I*(2*M_PI)*((k*n)/((float)N)));
    }

  *r = (1.0/N)*ret;
  return r;
}

