typedef struct filter_rl_t
{
  double R,L,T;
  double a;
  double b;
  double * last_value;
  unsigned long int n;
}filter_rl_t;

double filter_rl(struct filter_rl_t * f, const double new_sample);
void init_rl_filter(struct filter_rl_t * n, const double R, const double L, const double T, double * last_val, const unsigned long int size);
