#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "rc_filter.h"

int main(int argc, char **argv)
{
#define FREQ 42.0
#define OMEGA (FREQ*M_PI*2)
#define TIME 0.1
#define NUM_SAMPLES 10000
  struct filter_rc_t f;
  int c,i,a;
  char buf[100];
  float fl,r,cnd,timel;

  r=5000;
  cnd=4.7e-6;
  timel=1.0/NUM_SAMPLES;

  for(i=0;i<argc;i++)
    {
      if(!strncmp(argv[i],"-r",2))
	{
	  sscanf(argv[i+1],"%f\n",&r);
	}
      else if(!strncmp(argv[i],"-c",2))
	{
	  sscanf(argv[i+1],"%f\n",&cnd);
	}
      else if(!strncmp(argv[i],"-t",2))
	{
	  sscanf(argv[i+1],"%f\n",&timel);
	}
    }

  init_rc_filter(&f,r,cnd,timel);

  c=fgetc(stdin);
  i=0;
  a=0;
  while(c!=EOF)
    {
      if(c=='\n')
	{
	  sscanf(buf,"%f\n",&fl);
	  printf("%.5f\t%.5f\t%.5f\n",a*f.T,fl,filter_rc(&f,fl));
	  a++;
	  i=0;
	}
      buf[i]=(char)c;
      c=fgetc(stdin);
      i++;
    }

  return 0;
}
