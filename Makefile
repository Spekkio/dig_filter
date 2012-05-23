target: sim rc_filter.o square.o

sim: main.c rc_filter.o square.o main.h
	gcc -g -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -Wall -Wextra -Werror -o sim main.c rc_filter.o square.o

rc_filter.o: rc_filter.c rc_filter.h main.h
	gcc -g -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -Wall -Wextra -Werror -c rc_filter.c

square.o: square.c square.h
	gcc -g -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -Wall -Wextra -Werror -c square.c

clean:
	rm -rf sim \#*\# *.o *~
