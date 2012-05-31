#include <math.h>
#include "complex.h"
#include "fft.h"

/*exp (-i*2*Pi*(k/N)*n)*/
c_vector * fftv(c_vector * r, const c_vector * x, const unsigned long int N, const unsigned long int k)
{
  unsigned long int n;
  c_vector f,ret;

  ret.f[REAL] = 0;
  ret.f[IMAG] = 0;

  for(n=0;n<=(N-1);n++)
    {
      f.f[REAL] = 0;
      f.f[IMAG] = -2*M_PI*((k*n)/((float)N));
      i_expv(&f,f);
      i_mulv(&f,x[n],f);
      ret.v += f.v;
    }

  r->v = ret.v;
  return r;
}

c_vector * ifftv(c_vector * r, const c_vector * x, const unsigned long int N, const unsigned long int k)
{
  unsigned long int n;
  c_vector f,ret;

  ret.f[REAL] = 0;
  ret.f[IMAG] = 0;

  for(n=0;n<=(N-1);n++)
    {
      f.f[REAL] = 0;
      f.f[IMAG] = 2*M_PI*((k*n)/((float)N));
      i_expv(&f,f);
      i_mulv(&f,x[n],f);
      ret.v += f.v;
    }

  ret.f[REAL] *= (1.0/N);
  ret.f[IMAG] *= (1.0/N);
  r->v = ret.v;
  return r;
}

complex * fft(complex * r, const complex * x, const unsigned long int N, const unsigned long int k)
{
  unsigned long int n;
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

complex * ifft(complex * r, const complex * x, const unsigned long int N, const unsigned long int k)
{
  unsigned long int n;
  complex f,ret;

  ret.real = 0;
  ret.imag = 0;

  for(n=0;n<=(N-1);n++)
    {
      f.real = 0;
      f.imag = 2*M_PI*((k*n)/((float)N));
      i_exp(&f,f);
      i_mul(&f,x[n],f);
      i_add(&ret,ret,f);
    }

  r->real = (1.0/N)*ret.real;
  r->imag = (1.0/N)*ret.imag;
  return r;
}

