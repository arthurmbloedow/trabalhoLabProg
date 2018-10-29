trab: main.c funcs.c
	gcc -c main.c funcs.c
	gcc -o trab main.o funcs.o

all: trab

clean:
	rm *.o trab

