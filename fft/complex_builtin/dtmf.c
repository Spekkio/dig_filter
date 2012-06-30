#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <sndfile.h>
#include "fft.h"
#include "dtmf.h"

void decodeDTMF(char * filename)
{
  const unsigned int n_samples=30000;
  unsigned int samplesize, i;
  SNDFILE * f;
  FILE *plotfile;
  SF_INFO info;
  short sample;
  unsigned int rn_samples;
  float sec;
  float complex x[n_samples], r[n_samples];
 
  samplesize=0;
  samplesize=samplesize;

  for(i=0;i<n_samples;i++)
    {
      x[i] = 0.0 + _Complex_I*0.0;
      r[i] = 0.0 + _Complex_I*0.0;
    }

  f=sf_open(filename,SFM_READ,&info);
  if(f)
    {
      printf("Frames: %u\n",(unsigned int)info.frames);
      printf("Sample rate: %u\n",info.samplerate);
      printf("Channels: %u\n",info.channels);

      printf("Format: 0x%X\n",info.format);

      if((info.format & SF_FORMAT_WAV)==SF_FORMAT_WAV){
	printf("Format: SF_FORMAT_WAV\n");
      }
      if((info.format & SF_FORMAT_PCM_S8)==SF_FORMAT_PCM_S8){
	printf("\tSigned 8 bit data\n");
      }
      if((info.format & SF_FORMAT_PCM_U8)==SF_FORMAT_PCM_U8){
	printf("\tUnsigned 8 bit data\n");
      }
      if((info.format & SF_FORMAT_PCM_16)==SF_FORMAT_PCM_16){
	printf("\tSigned 16 bit data\n");
	samplesize=sizeof(int16_t);
      }
      if((info.format & SF_FORMAT_PCM_24)==SF_FORMAT_PCM_24){
	printf("\tSigned 24 bit data\n");
      }
      if((info.format & SF_FORMAT_PCM_32)==SF_FORMAT_PCM_32){
	printf("\tSigned 32 bit data\n"); 
      }
      if((info.format & SF_FORMAT_FLOAT)==SF_FORMAT_FLOAT){
	printf("\t32 bit float data\n");
      }
      if((info.format & SF_FORMAT_DOUBLE)==SF_FORMAT_DOUBLE){
	printf("\t64 bit float data\n");
      }
      printf("Sections: %u\n",info.sections);
      printf("Seekable: %u\n",info.seekable);

      rn_samples = info.samplerate / 1;

      sec = ((float)rn_samples)/((float)info.samplerate);
      printf("Seconds: %f\n",sec);
      printf("FPS: %f\n",1.0/sec);

      plotfile = fopen("dtmf_decode/plotfile.txt","w");

      if(plotfile){
	for(i=0;i<(rn_samples/10);i++)
	{
	  sf_readf_short(f,&sample, 1);
	  x[rn_samples-i] = (float)sample;
      	      /*fprintf(o,"%u\t%i\n",i,sample);*/
	}
      
      for(i=0;i<(rn_samples/2);i++)
	{
	  fft(&r[i],x,rn_samples,i);
	  fprintf(plotfile,"%f\t%.10f\n",i/sec,(cabs(r[i])*(2.0/rn_samples)));
	}
      }

      sf_close(f);
    }

}
