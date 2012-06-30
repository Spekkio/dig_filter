#include <values.h>
#include "main.h"
#include "convolution.h"

/*Integral[f(t-T)g(T),T->{0,t}]*/
double convolution_integral(void)
{
  return 0.0;
}

/*ret = A * Sum[B^n * new_sample]*/
double discrete_convolution(struct const_t * f, const double new_sample)
{
  double ret;
  unsigned long int i;

  ret = new_sample;
  f->last_value[f->n] = new_sample;

  if(f->n < NUM_VALUES)
    {
      if(((f->last_value[0]) <= MINFLOAT) &&
	 ((f->last_value[0]) >= -MINFLOAT) &&
	 (f->n >= 1))
	{
	  for(i=1;i<(f->n);i++)
	    {
	      f->last_value[i] *= f->b;
	      f->last_value[i-1] = f->last_value[i];
	      ret+=f->last_value[i];
	    }
	  f->last_value[i-1] = f->last_value[i];
	} else
	{
	  for(i=0;i<(f->n);i++)
	    {
	      f->last_value[i] *= f->b;
	      ret+=f->last_value[i];
	    }
	  f->n++;
	}
    }

  return ret*f->a;
}

void init_convolution(struct const_t * n, const double T, double * last_val, const unsigned long int size)
{
  unsigned long int i;
  n->T = T;
  n->n = 0;
  n->last_value = last_val;

  for(i=0;i<size;i++)
    {
      n->last_value[i] = 0;
    }  
}
