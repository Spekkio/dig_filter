typedef float v2sf __attribute__ ((vector_size(2*sizeof(float))));

typedef struct complex
{
  float real,imag;
}complex;

typedef union c_vector
{
  v2sf v;
  float f[2];
}c_vector;

complex * i_add(complex * r, const complex a, const complex b);
c_vector * i_addv(c_vector * r, const c_vector a, const c_vector b);
complex * i_sub(complex * r, const complex a, const complex b);
c_vector * i_subv(c_vector * r, const c_vector a, const c_vector b);
complex * i_mul(complex * r, const complex a, const complex b);
complex * i_div(complex * r, const complex a, const complex b);
complex * i_exp(complex * r, const complex a);
complex * i_sqrt(complex * r, const complex a);
float i_abs(const complex a);
