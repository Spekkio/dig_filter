#include "rc_filter.h"

double filter_rc(struct filter_rc_t * f, const double new_sample)
{
  double ret=new_sample;
  unsigned long int i;
  f->last_value[f->n] = new_sample;

  for(i=0;i<(f->n);i++)
    {
      f->last_value[i] *= f->b;
      ret+=f->last_value[i];
    }
  f->n++;  

  return ret*f->a;
}

void init_rc_filter(struct filter_rc_t * n, const double R, const double C, const double T)
{
  unsigned long int i;
  n->R = R;
  n->C = C;
  n->T = T;
  n->a = (4*C*R*T)/(4*(C*R)*(C*R)-T*T);
  n->b = (-1 + (4)/(2+T/(C*R)));
  n->n = 0;

  for(i=0;i<0xFFFF;i++)
    {
      n->last_value[i] = 0;
    }  
}
