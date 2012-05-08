#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct filter_rc_t
{
  double R,C,T;
  double a;
  double b;
  double last_value[0xFFFF];
  unsigned long int n;
}filter_t;

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

int main(void)
{
#define FREQ 42.0
#define OMEGA (FREQ*M_PI*2)
#define TIME 0.1
#define NUM_SAMPLES 10000
  struct filter_rc_t f;
  int i;
  
  init_rc_filter(&f,5000,4.7e-6,1.0/NUM_SAMPLES);

  for(i=0;i<=((int)(TIME/f.T));i++)
    {
      printf("%.52f\t%.52f\t",i*f.T,filter_rc(&f,sin(OMEGA*(i*f.T))));
      printf("%.52f\n",f.last_value[1]);
    }

  return 0;
}
