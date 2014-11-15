MAZE_C_FLAGS=-g -Wall -Wextra -Waggregate-return -Wcast-align -Wcast-qual -Wconversion -Wformat=2 -Winline -Wlong-long -Wmissing-prototypes -Wmissing-declarations -Wnested-externs -Wno-import -Wpointer-arith -Wredundant-decls -Wreturn-type -Wshadow -Wstrict-prototypes -Wswitch -Wwrite-strings -Wvla

maze_debug.exe: maze_debug.o mtrand_debug.o html5_debug.o
	gcc -g -o maze_debug.exe maze_debug.o mtrand_debug.o html5_debug.o

maze_debug.o: ../mtrand.h ../html5.h ../maze.c maze.make
	gcc -c ${MAZE_C_FLAGS} -o maze_debug.o ../maze.c

mtrand_debug.o: ../mtrand.h ../mtrand.c maze.make
	gcc -c ${MAZE_C_FLAGS} -o mtrand_debug.o ../mtrand.c

html5_debug.o: ../html5.h ../html5.c maze.make
	gcc -c ${MAZE_C_FLAGS} -o html5_debug.o ../html5.c
