objects := rc_filter.o rl_filter.o square.o
all_objects := sim $(objects)

target: $(all_objects)

sim: main.c main.h $(objects)
	gcc -g -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -Wall -Wextra -Werror -o sim main.c $(objects)

rc_filter.o: rc_filter.c rc_filter.h main.h
	gcc -g -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -Wall -Wextra -Werror -c rc_filter.c

rl_filter.o: rl_filter.c rl_filter.h main.h
	gcc -g -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -Wall -Wextra -Werror -c rl_filter.c

square.o: square.c square.h
	gcc -g -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -Wall -Wextra -Werror -c square.c

clean:
	rm -rf $(all_objects) \#*\# *~
