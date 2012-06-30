standard = -std=c99
debug = -g
optimize = -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math 
optimize_ = 
options = -pedantic $(standard) $(debug) -Wall -Wextra -Werror 
libs = -lm -lsndfile

objects = fft.o dtmf.o


target: fft $(objects)

fft: main.c $(objects)
	gcc $(optimize) $(options) -o fft main.c $(objects) $(libs)

fft.o: fft.c fft.h
	gcc $(optimize) $(options) -c fft.c

dtmf.o: dtmf.c dtmf.h
	gcc $(optimize) $(options) -c dtmf.c

clean:
	rm -rf fft *.o *~
