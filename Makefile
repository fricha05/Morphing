CC=gcc
CFLAGS= -ansi -Wall -pedantic
LIBFLAGS= -lm -lMLV
OBJ = Main.o Graphics.o Triangulation.o 

Morphing: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBFLAGS)

Main.o: src/Main.c include/Graphics.h

Graphics.o: src/Graphics.c include/Graphics.h include/Triangulation.h

Triangulation.o: src/Triangulation.c include/Triangulation.h


%.o: src/%.c
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f *.o
	rm -f include/*.gch
mrproper: clean
	rm -f Morphing
install: Morphing
	mkdir bin
	mv Morphing bin/Morphing
	make mrproper
uninstall: mrproper
	rm -f bin/Morphing
	rm -rf bin
