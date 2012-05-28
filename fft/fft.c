#include <math.h>
#include "complex.h"
#include "fft.h"

/*exp (-i*2*Pi*(k/N)*n)*/
complex * fft(complex * r, const complex * x, const unsigned int N, const unsigned int k)
{
  unsigned int n;
  complex f,ret;

  ret.real = 0;
  ret.imag = 0;

  for(n=0;n<=(N-1);n++)
    {
      f.real = 0;
      f.imag = -2*M_PI*((k*n)/((float)N));
      i_exp(&f,f);
      i_mul(&f,x[n],f);
      i_add(&ret,ret,f);
    }

  r->real = ret.real;
  r->imag = ret.imag;
  return r;
}

