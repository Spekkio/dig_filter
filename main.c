#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "rc_filter.h"
#include "rl_filter.h"
#include "square.h"
#include "main.h"

double * values; /*67 MByte RAM*/

int main(int argc, char **argv)
{
#define FREQ 42.0
#define OMEGA (FREQ*M_PI*2)
#define TIME 0.1
#define NUM_SAMPLES 10000
  struct filter_rc_t f_rc;
  struct filter_rl_t f_rl;
  int c,i,a;
  char buf[100];
  unsigned long int type;
  unsigned int iter;
  float fl,r,cnd,timel,freq,ampl,time_i,time_limit,inductor;

  r=5000;
  cnd=4.7e-6;
  timel=1.0/NUM_SAMPLES;
  freq=120;
  ampl=3.3;
  iter=10;
  inductor=300e-3;
  time_limit=5;
  type=0;
  type=RC_TYPE;

  for(i=0;i<argc;i++)   
    {
      if(!strncmp(argv[i],"-timestamp",10))
	{
	  type|=TIMESTAMP;
	}
      else if(!strncmp(argv[i],"-limit",6))
	{
	  sscanf(argv[i+1],"%f\n",&time_limit);
	}
      else if(!strncmp(argv[i],"-i",2))
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
	  else if(!strncmp(argv[i+1],"rl",2))
	    {
	      type=RL_TYPE;
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
      else if(!strncmp(argv[i],"-ind",4))
	{
	  sscanf(argv[i+1],"%f\n",&inductor);
	}
      else if(!strncmp(argv[i],"-t",2))
	{
	  sscanf(argv[i+1],"%f\n",&timel);
	}
    }


  switch(type & 0xFF)
    {
    case RC_TYPE:
      values = malloc(sizeof(double)*NUM_VALUES);
      init_rc_filter(&f_rc,r,cnd,timel,&values[0],NUM_VALUES);
      c=fgetc(stdin);
      i=0;
      a=0;
      while((c!=EOF) && (a*f_rc.T <= time_limit))
	{
	  if(c=='\n')
	    {
	      sscanf(buf,"%f\n",&fl);
	      if(type & TIMESTAMP)
		{
		  printf("%.52f\t%.52f\n",a*f_rc.T,filter_rc(&f_rc,fl));
		}else
		{
		  printf("%.52f\n",filter_rc(&f_rc,fl));
		}
	      a++;
	      i=0;
	    }
	  buf[i]=(char)c;
	  c=fgetc(stdin);
	  i++;
	}
      free(values);
      break;

    case RL_TYPE:
      values = malloc(sizeof(double)*NUM_VALUES);
      init_rl_filter(&f_rl,r,inductor,timel,&values[0],NUM_VALUES);
      c=fgetc(stdin);
      i=0;
      a=0;
      while((c!=EOF) && (a*f_rl.T <= time_limit))
	{
	  if(c=='\n')
	    {
	      sscanf(buf,"%f\n",&fl);
	      if(type & TIMESTAMP)
		{
		  printf("%.52f\t%.52f\n",a*f_rl.T,filter_rl(&f_rl,fl));
		}else
		{
		  printf("%.52f\n",filter_rl(&f_rl,fl));
		}
	      a++;
	      i=0;
	    }
	  buf[i]=(char)c;
	  c=fgetc(stdin);
	  i++;
	}
      free(values);
      break;

    case SQUARE_TYPE:
      time_i=0.0;
      if((type & TIMESTAMP) == TIMESTAMP)
	{
	  while(time_i <= time_limit)
	    {
	      printf("%.52f\t%.52f\n",time_i,square_w(ampl, freq, iter, time_i));
	      time_i+=timel;
	    }
	}
      else
	{
	  while(time_i <= time_limit)
	    {
	      printf("%.52f\n",square_w(ampl, freq, iter, time_i));
	      time_i+=timel;
	    }
	}
      break;

    default:
      break;
    }

  return 0;
}
