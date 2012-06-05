#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <sndfile.h>
#include "fft.h"

void makeWav(char * filename, sf_count_t n_samples, float complex *samples);

void makeWav(char * filename, sf_count_t n_samples, float complex *samples)
{
  sf_count_t i;
  int count;
  SNDFILE * f;
  SF_INFO info;
  float temp;

  info.samplerate = n_samples;
  info.channels = 1;
  info.format = SF_FORMAT_WAV | SF_FORMAT_FLOAT | SF_ENDIAN_FILE;

  f=sf_open(filename,SFM_WRITE,&info);
  if(f)
    {
      for(i=0,count=0;i<n_samples;i++,count++)
	{
	  temp=cabs(samples[count]);
	  sf_write_float(f, &temp, 1);
	}
      sf_close(f);
    }
}

int main()
{
  /*
  #define SAMPLE_TIME 1.0
  #define S_TIME 0.1
  #define S_FREQ (1.0/S_TIME)

  #define MAX_FREQ 15
  #define SAMPLES ((unsigned long int)(SAMPLE_TIME*S_TIME))
  #define SECONDS (S_TIME/SAMPLES)
  */

  #define SAMPLES 22050
  #define SECONDS 1.0
  #define S_TIME (SECONDS/SAMPLES)
  #define S_FREQ (1.0/S_TIME)
  
  #define FREQ 1002
  #define FREQ2 1001
  #define FREQ3 1000
  #define FFTs 1000

  float i;
  int a;
  float complex x[SAMPLES],r[SAMPLES],z;

  z = 0 + _Complex_I*0;

  for(i=0.0,a=0;i<SECONDS;i+=S_TIME,a++)
    {
      x[a] = 0.5*sin(i*2*M_PI*FREQ)+0.8*sin(i*2*M_PI*FREQ2)+1.0*sin(i*2*M_PI*FREQ3)+5.0*(((float)rand()/RAND_MAX)-0.5) + _Complex_I*0;
      /*x[a].f[REAL] = 1.0*sin(i*2*M_PI*10);*/
      /*
      printf("%.52f\t%.52f\n",i,x[a].f[REAL]);
      */
    }

  makeWav("test1.wav",SAMPLES,x);

  /*X[k] = Sum[x[n]*exp(-I*2*Pi*(k*n)/N),{n,0,N-1}]*/
  /*fft(&result, input array x, number of array items N, Index k of result X[k])*/  
  
  for(a=0;a<=(SAMPLES);a++)
    {
      fft(&r[a],x,SAMPLES,a);
      /*
      printf("%.6e\t%.6e\n",((float)a)/SECONDS,cabs(r[a])*(2.0/SAMPLES));
      */
      if((cabs(r[a])*(2.0/SAMPLES))<0.25)
	{
	  r[a] = z;
	}
    }

  for(a=0;a<=(SAMPLES);a++)
    {
      ifft(&x[a],r,SAMPLES,a);
      /*printf("%f\t%.52f\n",a*S_TIME,creal(x[a]));*/
    }

  makeWav("test2.wav",SAMPLES,x);

  return 0;
}
