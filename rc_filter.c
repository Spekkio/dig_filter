#include <stdio.h>
#include <values.h>
#include "rc_filter.h"

double filter_rc(struct filter_rc_t * f, const double new_sample)
{
  double ret;
  unsigned long int i;

  ret = new_sample;
  f->last_value[f->n] = new_sample;

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

  return ret*f->a;
}

void init_rc_filter(struct filter_rc_t * n, const double R, const double C, const double T, double * last_val, const unsigned long int size)
{
  unsigned long int i;
  n->R = R;
  n->C = C;
  n->T = T;
  n->a = (4*C*R*T)/(4*(C*R)*(C*R)-T*T);
  n->b = (-1 + (4)/(2+T/(C*R)));
  n->n = 0;
  n->last_value = last_val;

  for(i=0;i<size;i++)
    {
      n->last_value[i] = 0;
    }  
}
