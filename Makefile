all: main.o
	[ ! -d dist ] && mkdir dist
	gcc -o dist/bell main.o

main.o: main.c
	gcc -c main.c

clean:
	rm -f bell *.o	
