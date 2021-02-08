all: anasin

anasin: anasin.c sintax.o listas.o
	gcc -g -Wall -I ./ -o anasin anasin.c sintax.o listas.o

sintax.o: sintax.c
	gcc -g -Wall -I ./ -c sintax.c
	
listas.o: listas.c
	gcc -g -Wall -I ./ -c listas.c
	
clean:
	rm *.o anasin