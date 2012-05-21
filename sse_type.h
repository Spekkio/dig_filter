typedef float v4sf __attribute__ ((vector_size(4*sizeof(float))));

union float4v 
{
  v4sf v;
  float f[4];
};

