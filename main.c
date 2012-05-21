#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "rc_filter.h"
#include "square.h"

#define RC_TYPE 1
#define SQUARE_TYPE 2

int main(int argc, char **argv)
{
#define FREQ 42.0
#define OMEGA (FREQ*M_PI*2)
#define TIME 0.1
#define NUM_SAMPLES 10000
  struct filter_rc_t f;
  int c,i,a;
  char buf[100];
  int type;
  unsigned int iter;
  float fl,r,cnd,timel,freq,ampl,time_i;

  r=5000;
  cnd=4.7e-6;
  timel=1.0/NUM_SAMPLES;
  freq=120;
  ampl=3.3;
  iter=10;
  type=RC_TYPE;

  for(i=0;i<argc;i++)
    {
      if(!strncmp(argv[i],"-i",2))
	{
	  sscanf(argv[i+1],"%ui\n",&iter);  
	}
      else if(!strncmp(argv[i],"-A",2))
	{
	  sscanf(argv[i+1],"%f\n",&ampl);  
	}
      else if(!strncmp(argv[i],"-type",5))
	{
	  if(!strncmp(argv[i+1],"rc",2))
	    {
	      type=RC_TYPE;
	    }
	  else if(!strncmp(argv[i+1],"square",6))
	    {
	      type=SQUARE_TYPE;
	    }
	}
      else if(!strncmp(argv[i],"-f",2))
	{
	  sscanf(argv[i+1],"%f\n",&freq);
	}
      else if(!strncmp(argv[i],"-r",2))
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


  switch(type)
    {
    case RC_TYPE:
      init_rc_filter(&f,r,cnd,timel);
      c=fgetc(stdin);
      i=0;
      a=0;
      while(c!=EOF)
	{
	  if(c=='\n')
	    {
	      sscanf(buf,"%f\n",&fl);
	      /*printf("%.5f\t%.5f\t%.5f\n",a*f.T,fl,filter_rc(&f,fl));*/
	      printf("%.5f\t%.5f\n",fl,filter_rc(&f,fl));
	      a++;
	      i=0;
	    }
	  buf[i]=(char)c;
	  c=fgetc(stdin);
	  i++;
	}
      break;

    case SQUARE_TYPE:
      time_i=0.0;
      while(1)
	{
	  printf("%f\n",square_w(ampl, freq, iter, time_i));
	  time_i+=timel;
	}
      break;

    default:
      break;
    }

  return 0;
}
