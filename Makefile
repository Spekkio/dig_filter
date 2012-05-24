objects := fir_filter.o square.o convolution.o
all_objects := sim $(objects)

target: $(all_objects)

sim: main.c main.h $(objects)
	gcc -g -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -Wall -Wextra -Werror -o sim main.c $(objects)

fir_filter.o: fir_filter.c fir_filter.h main.h
	gcc -g -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -Wall -Wextra -Werror -c fir_filter.c

square.o: square.c square.h
	gcc -g -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -Wall -Wextra -Werror -c square.c

convolution.o: convolution.c convolution.h
	gcc -g -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -Wall -Wextra -Werror -c convolution.c

clean:
	rm -rf $(all_objects) \#*\# *~

clean_plots:
	rm -rf *.plt *.txt
