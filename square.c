#include "sse_type.h"
#include "square.h"
#include <math.h>
#include <stdio.h>

const float Pi = 3.1415926535897932384626433832795;

float square_w(const float V, const float F, const unsigned int N, const float t)
{
  union float4v nv,in_sin,tv,out;
  union float4v Fv,Vv,PIv,two,minus_one,one,half;

  unsigned int n;

  two.f[0] = (const float)2;
  two.f[1] = (const float)2;
  two.f[2] = (const float)2;
  two.f[3] = (const float)2;

  out.f[0] = (const float)0.0;
  out.f[1] = (const float)0.0;
  out.f[2] = (const float)0.0;
  out.f[3] = (const float)0.0;

  half.f[0] = (const float)0.5;
  half.f[1] = (const float)0.0;
  half.f[2] = (const float)0.0;
  half.f[3] = (const float)0.0;

  minus_one.f[0] = (const float)-1.0;
  minus_one.f[1] = (const float)-1.0;
  minus_one.f[2] = (const float)-1.0;
  minus_one.f[3] = (const float)-1.0;

  one.f[0] = (const float)4.0;
  one.f[1] = (const float)4.0;
  one.f[2] = (const float)4.0;
  one.f[3] = (const float)4.0;

  Fv.f[0] = (const float)F;
  Fv.f[1] = (const float)F;
  Fv.f[2] = (const float)F;
  Fv.f[3] = (const float)F;

  PIv.f[0] = (const float)Pi;
  PIv.f[1] = (const float)Pi;
  PIv.f[2] = (const float)Pi;
  PIv.f[3] = (const float)Pi; 
  
  Vv.f[0] = (const float)V;
  Vv.f[1] = (const float)V;
  Vv.f[2] = (const float)V;
  Vv.f[3] = (const float)V;
  
  tv.f[0] = t;
  tv.f[1] = t;
  tv.f[2] = t;
  tv.f[3] = t;

  nv.f[0] = (float)(1);
  nv.f[1] = (float)(2);
  nv.f[2] = (float)(3);
  nv.f[3] = (float)(4);

  for(n=0;n<N;n++)
    {
      in_sin.v = two.v*Fv.v*(minus_one.v + two.v*nv.v)*PIv.v*tv.v;
      in_sin.f[0] = sin(in_sin.f[0]);
      in_sin.f[1] = sin(in_sin.f[1]);
      in_sin.f[2] = sin(in_sin.f[2]);
      in_sin.f[3] = sin(in_sin.f[3]);

      in_sin.v /= ((minus_one.v + two.v*nv.v)*PIv.v);
      in_sin.v *= two.v;
      out.v += in_sin.v;
      nv.v = nv.v + one.v;
    }

  out.v += half.v;
  out.v *= Vv.v;

  return out.f[0] + out.f[1]+ out.f[2]+ out.f[3];
}
