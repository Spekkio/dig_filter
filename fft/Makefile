objects = complex.o fft.o

target: fft $(objects)

fft: main.c $(objects)
	gcc -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -g -Wall -Wextra -Werror -o fft main.c $(objects) -lm

complex.o: complex.c complex.h
	gcc -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -g -Wall -Wextra -Werror -c complex.c

fft.o: fft.c fft.h
	gcc -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -g -Wall -Wextra -Werror -c fft.c

clean:
	rm -rf fft *.o *~
