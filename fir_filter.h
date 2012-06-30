#include "convolution.h"

typedef struct filter_rc_t
{
  double R,C;
  const_t consts;
}filter_rc_t;

typedef struct filter_rl_t
{
  double R,L;
  const_t consts;
}filter_rl_t;

void init_rc_filter(struct filter_rc_t * n, const double R, const double C, const double T, double * last_val, const unsigned long int size);
void init_lr_filter(struct filter_rl_t * n, const double R, const double L, const double T, double * last_val, const unsigned long int size);
