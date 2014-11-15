MAZE_C_FLAGS=-O2 -Wall -Wextra -Waggregate-return -Wcast-align -Wcast-qual -Wconversion -Wformat=2 -Winline -Wlong-long -Wmissing-prototypes -Wmissing-declarations -Wnested-externs -Wno-import -Wpointer-arith -Wredundant-decls -Wreturn-type -Wshadow -Wstrict-prototypes -Wswitch -Wwrite-strings -Wvla

maze.exe: maze.o mtrand.o html5.o
	gcc -o maze.exe maze.o mtrand.o html5.o

maze.o: ../mtrand.h ../html5.h ../maze.c maze.make
	gcc -c ${MAZE_C_FLAGS} -o maze.o ../maze.c

mtrand.o: ../mtrand.h ../mtrand.c maze.make
	gcc -c ${MAZE_C_FLAGS} -o mtrand.o ../mtrand.c

html5.o: ../html5.h ../html5.c maze.make
	gcc -c ${MAZE_C_FLAGS} -o html5.o ../html5.c
