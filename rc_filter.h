typedef struct filter_rc_t
{
  double R,C,T;
  double a;
  double b;
  double * last_value;
  unsigned long int n;
}filter_t;

double filter_rc(struct filter_rc_t * f, const double new_sample);
void init_rc_filter(struct filter_rc_t * n, const double R, const double C, const double T, double * last_val, const unsigned long int size);
