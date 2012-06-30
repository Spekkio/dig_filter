#include <stdio.h>
#include <values.h>
#include "main.h"
#include "fir_filter.h"

void init_rc_filter(struct filter_rc_t * n, const double R, const double C, const double T, double * last_val, const unsigned long int size)
{
  init_convolution(&n->consts, T, last_val, size);
  n->R = R;
  n->C = C;
  n->consts.a = (4*C*R*T)/(4*(C*R)*(C*R)-T*T);
  n->consts.b = (-1 + (4)/(2+T/(C*R)));
}

void init_cr_filter(struct filter_rc_t * n, const double R, const double C, const double T, double * last_val, const unsigned long int size)
{
  init_convolution(&n->consts, T, last_val, size);
  n->R = R;
  n->C = C;
  n->consts.a = -(4*C*R*T)/(4*(C*R)*(C*R)-T*T);
  n->consts.b = (-1 + (4)/(2+T/(C*R)));
}

void init_lr_filter(struct filter_rl_t * n, const double R, const double L, const double T, double * last_val, const unsigned long int size)
{
  init_convolution(&n->consts, T, last_val, size);
  n->R = R;
  n->L = L;
  n->consts.a = (4*L*R*T)/(4*L*L-R*R*T*T);
  n->consts.b = (-1 + 4/(2+((R*T)/L)));
}

void init_rl_filter(struct filter_rl_t * n, const double R, const double L, const double T, double * last_val, const unsigned long int size)
{
  init_convolution(&n->consts, T, last_val, size);
  n->R = R;
  n->L = L;
  n->consts.a = -(4*L*R*T)/(4*L*L-R*R*T*T);
  n->consts.b = (-1 + 4/(2+(R*T/L)));
}
