target: main

main: main.c 
	gcc -pedantic -O3 -msse3 -msse4.1 -msse4.2 -mfpmath=both -ffast-math -g -Wall -Wextra -Werror -o main main.c
#	gcc -pedantic -g -Wall -Wextra -Werror -o main main.c -lm
clean:
	rm -rf main *.o *~
