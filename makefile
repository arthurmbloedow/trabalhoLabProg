trab: main.c funcs.c
	gcc -c main.c funcs.c
	gcc -o trab main.o funcs.o -L"/usr/local/lib" -lhpdf

all: trab

clean:
	rm *.o trab

