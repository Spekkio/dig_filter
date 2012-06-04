objects = fft.o

target: fft $(objects)

fft: main.c $(objects)
	gcc -pedantic -std=c99 -O9 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -g -Wall -Wextra -Werror -o fft main.c $(objects) -lm

fft.o: fft.c fft.h
	gcc -pedantic -std=c99 -O9 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -g -Wall -Wextra -Werror -c fft.c

clean:
	rm -rf fft *.o *~
