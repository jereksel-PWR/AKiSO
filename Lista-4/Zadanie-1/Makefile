all: bash

bash: bash.o
	gcc bash.o -o bash

bash.o: bash.c
	gcc -c bash.c

clean:
	rm -rf *o bash
