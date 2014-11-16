maze-and-path
=============

Maze and Path generator written in C, algorithms used are Kruskal for maze creation and Breadth First Search for path generation.

Unix makefiles and Windows solution provided.

Parameters are read on standard input (example available in maze.input).

400 200 1,1 400,200 0 means "Maze 400x200 - Path from 1,1 to 400,200 - No output"

Last parameter holds output format: 0 - No output, 1 - Text, 2 - HTML.

Maze and Path are displayed on standard output.
