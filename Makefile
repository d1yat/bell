all: main.o
	mkdir -p dist
	gcc -o dist/bell main.o

main.o: main.c
	gcc -c main.c

clean:
	rm -f bell *.o	
