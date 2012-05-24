#include <stdio.h>
#include <values.h>
#include "main.h"
#include "rl_filter.h"

/*
Vin    R
-----/\/\/\----+ Vout
               |
               |
               {
               } L
               {
               |
	      GND
 */

double filter_rl(struct filter_rl_t * f, const double new_sample)
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

void init_rl_filter(struct filter_rl_t * n, const double R, const double L, const double T, double * last_val, const unsigned long int size)
{
  unsigned long int i;
  n->R = R;
  n->L = L;
  n->T = T;
  n->a = (-4*L*R*T)/(4*L*L-R*R*T*T);
  n->b = (2*L-R*T)/(2*L+R*T);
  n->n = 0;
  n->last_value = last_val;

  for(i=0;i<size;i++)
    {
      n->last_value[i] = 0;
    }  
}
