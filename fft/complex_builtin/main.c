#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <sndfile.h>
#include "fft.h"
#include "dtmf.h"

#define TEST 44100
#define MIN_FREQ 1000
#define MAX_FREQ 2000

void makeWav(const char * filename, const sf_count_t samplerate, const unsigned int n_samples, const float complex *samples);
void readWav(char * filename);

void readWav(char * filename)
{
  unsigned int n_samples, int_samples;
  SNDFILE * f;
  FILE *o, *li;
  SF_INFO info;
  int samplesize, i, a;
  /*short sample;*/
  char outfile[20];
  float sec, fps, float_sample, freq_interval;
  float complex x[TEST], r[TEST];

  fps = 30.0;
  freq_interval = 5.0;
  freq_interval =   freq_interval;

  for(i=0;i<TEST;i++)
    {
      x[i] = 0.0 + _Complex_I*0.0;
      r[i] = 0.0 + _Complex_I*0.0;
    }

  samplesize = 0;
  samplesize = samplesize;

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

      /*
      n_samples = info.samplerate / fps;
      int_samples = info.samplerate / freq_interval;
      */

      n_samples = 1500;
      int_samples = n_samples;

      sec = ((float)int_samples)/((float)info.samplerate);

      /*sec = 1.0;*/
      printf("Seconds: %f\n",sec);
      printf("FPS: %f\n",1/sec);
      printf("Pre FPS: %f\n",fps);

      li=fopen("tmp/filelist.list","w");

      if(li)
      for(a=0;(a*n_samples)<((unsigned int)info.frames);a++) {
	/*
      printf("%.2f\n",((float)a*TEST)/((float)info.frames)*100.0);
	*/
      snprintf(outfile, 20, "tmp/plot%06u.txt", a);
      o=fopen(outfile, "w");

      fprintf(li,"%s.jpg ", &outfile[4]);

      if(o)
	{
	  for(i=0;i<((int)n_samples);i++)
	    {
	      /*
	      sf_readf_short(f,&sample, 1);
	      */
	      sf_readf_float(f,&float_sample, 1);
	      x[i] = (float)float_sample;
      	      /*fprintf(o,"%u\t%i\n",i,sample);*/
	    }

	  /*for(i=MIN_FREQ; (i<(((int)info.samplerate)/2)) && (i<MAX_FREQ);i++)*/
	  for(i=(MIN_FREQ*sec); (i<(((int)int_samples)/2)) && (i<(MAX_FREQ*sec));i++)
	    {
	      fft(&r[i],x,int_samples,i);
	      fprintf(o,"%f\t%.10f\n",(float)i/sec,(cabs(r[i])*(2.0/((float)int_samples))));
	    }

	  /*shift back*/

	  /*
	  i=(info.samplerate-1);
	  while(i>=(int)n_samples)
	    {
	      x[i] = x[i-n_samples];
	      i--;
	    }
	  */

	  fclose(o);
	}
      }

      fclose(li);
      sf_close(f);
    }

}

void makeWav(const char * filename, const sf_count_t samplerate, const unsigned int n_samples, const float complex *samples)
{
  sf_count_t i;
  unsigned int count;
  SNDFILE * f;
  SF_INFO info;
  float temp;
  /*short samp;*/

  info.samplerate = samplerate;
  info.channels = 1;
  info.format = SF_FORMAT_WAV | SF_FORMAT_FLOAT | SF_ENDIAN_FILE;

  f=sf_open(filename,SFM_WRITE,&info);
  if(f)
    {
      for(i=0,count=0;i<n_samples;i++,count++)
	{
	  /*
	  samp=(short)cabs(samples[count]);
	  sf_write_short(f, &samp, 1);
	  */
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
  #define S_TIME (1.0/SAMPLES)
  #define S_FREQ (1.0/S_TIME)
  
  #define FREQ 1002
  #define FREQ2 1001
  #define FREQ3 1000
  #define FFTs 1000

  char msg[] = "Spekkio";
  float i;
  int a,m_c,fs;
  float complex x[SAMPLES*7];
  float complex r[SAMPLES];

  /*  
  readWav("dtmf.BLheUl.wav");
  */

  /*
  decodeDTMF("dtmf.BLheUl.wav");
  */

  m_c = 0;
  for(i=0.0,a=0;i<(SECONDS);i+=S_TIME,a++)
    {
      m_c = (unsigned int)i;
      x[a] = 0.0 + _Complex_I*0;
      for(fs=0;fs<8;fs++)
	{
	  if((msg[m_c] & (1<<fs)) == (1<<fs))
	    {
	      x[a] += 1.0*sin(i*2*M_PI*(1000+100*fs)) + _Complex_I*0;
	    }
	}
    }

  /*
  makeWav("test1.wav",SAMPLES,SAMPLES*7,x);
  readWav("test1.wav");
  */

  for(a=0;a<=(SAMPLES/2);a++)
    {
      fft(&r[a],x,SAMPLES,a);
      printf("%f\t%f\n",a/SECONDS,cabs(r[a])*(2.0/SAMPLES));
      /*
      if((cabs(r[a])*(2.0/SAMPLES))<0.25)
	{
	  r[a] = z;
	}
      */
    }

  /*
  for(a=0;a<=(SAMPLES);a++)
    {
      ifft(&x[a],r,SAMPLES,a);
    }
  makeWav("test2.wav",SAMPLES,x);
  */

  return 0;
}
