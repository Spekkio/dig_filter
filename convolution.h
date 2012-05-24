typedef struct const_t
{
  double T;
  double a;
  double b;
  double * last_value;
  unsigned long int n;
}const_t;

double discrete_convolution(struct const_t * f, const double new_sample);
void init_convolution(struct const_t * n, const double T, double * last_val, const unsigned long int size);
