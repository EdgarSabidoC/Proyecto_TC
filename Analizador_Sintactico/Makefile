all: anasin

anasin: anasin.c sintax.o listassin.o
	gcc -g -Wall -I ./ -o anasin anasin.c sintax.o listassin.o

sintax.o: sintax.c
	gcc -g -Wall -I ./ -c sintax.c
	
listassin.o: listassin.c
	gcc -g -Wall -I ./ -c listassin.c
	
clean:
	rm *.o anasin