#include <math.h>
#include "complex.h"

complex * i_add(complex * r, const complex a, const complex b)
{
  r->real = a.real + b.real;
  r->imag = a.imag + b.imag;
  return r;
}

c_vector * i_addv(c_vector * r, const c_vector a, const c_vector b)
{
  r->v = a.v + b.v;
  return r;
}

complex * i_sub(complex * r, const complex a, const complex b)
{
  r->real = a.real - b.real;
  r->imag = a.imag - b.imag;
  return r;
}

c_vector * i_subv(c_vector * r, const c_vector a, const c_vector b)
{
  r->v = a.v - b.v;
  return r;
}

complex * i_mul(complex * r, const complex a, const complex b)
{
  complex temp;
  temp.real = a.real*b.real - a.imag*b.imag;
  temp.imag = a.real*b.imag + a.imag*b.real; 
  r->real = temp.real;
  r->imag = temp.imag;
  return r;
}

c_vector * i_mulv(c_vector * r, const c_vector a, const c_vector b)
{
  c_vector temp;
  temp.f[REAL] = a.f[REAL]*b.f[REAL] - a.f[IMAG]*b.f[IMAG];
  temp.f[IMAG] = a.f[REAL]*b.f[IMAG] + a.f[IMAG]*b.f[REAL];
  r->v = temp.v;
  return r;
}

/*
complex * i_div(complex * r, const complex a, const complex b)
{
  return r;
}
*/

/*exp(a.real)*exp(i*a.imag) = exp(a.real)*(cos(a.imag)+i*sin(a.imag))*/
complex * i_exp(complex * r, const complex a)
{
  complex temp;
  temp.real = exp(a.real) * cos(a.imag);
  temp.imag = exp(a.real) * sin(a.imag);
  r->real = temp.real;
  r->imag = temp.imag;
  return r;
}

c_vector * i_expv(c_vector * r, const c_vector a)
{
  c_vector temp;
  temp.f[REAL] = exp(a.f[REAL]) * cos(a.f[IMAG]);
  temp.f[IMAG] = exp(a.f[REAL]) * sin(a.f[IMAG]);
  r->v = temp.v;
  return r;
}

complex * i_sqrt(complex * r, const complex a)
{
  complex temp;
  temp.real = sqrt((a.real + sqrt(a.real*a.real + a.imag*a.imag))/2);
  temp.imag = sqrt((-a.real+sqrt(a.real*a.real + a.imag*a.imag))/2);
  r->real = temp.real;
  r->imag = temp.imag;
  return r;
}

c_vector * i_sqrtv(c_vector * r, const c_vector a)
{
  c_vector temp;
  temp.f[REAL] = sqrt((a.f[REAL] + sqrt(a.f[REAL]*a.f[REAL] + a.f[REAL]*a.f[IMAG]))/2);
  temp.f[IMAG] = sqrt((-a.f[REAL]+sqrt(a.f[REAL]*a.f[REAL] + a.f[IMAG]*a.f[IMAG]))/2);
  r->v = temp.v;
  return r;
}

float i_abs(const complex a)
{
  return sqrt(a.real*a.real + a.imag*a.imag);
}


float i_absv(const c_vector a)
{
  return sqrt(a.f[REAL]*a.f[REAL] + a.f[IMAG]*a.f[IMAG]);
}
