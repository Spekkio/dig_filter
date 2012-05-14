target: main rc_filter.o

main: main.c rc_filter.o
	gcc -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -g -Wall -Wextra -Werror -o main main.c rc_filter.o

rc_filter.o: rc_filter.c rc_filter.h
	gcc -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -g -Wall -Wextra -Werror -c rc_filter.c

clean:
	rm -rf main *.o *~
