all: bin/prog 

bin/prog: obj/board.o obj/tetromino.o obj/interface.o obj/carte.o obj/main.o
	gcc -Wall -Wextra -std=c99 obj/board.o obj/tetromino.o obj/interface.o obj/carte.o obj/main.o -o bin/prog

obj/tetromino.o: src/tetromino.c include/tetromino.h 
	gcc -Wall -Wextra -std=c99 -c src/tetromino.c -o obj/tetromino.o

obj/board.o: src/board.c include/board.h include/tetromino.h include/carte.h
	gcc -Wall -Wextra -std=c99 -c src/board.c -o obj/board.o


obj/interface.o: src/interface.c include/interface.h include/board.h include/tetromino.h
	gcc -Wall -Wextra -std=c99 -c src/interface.c -o obj/interface.o

obj/carte.o : include/carte.h src/carte.c 
	gcc -Wall -Wextra -std=c99 -c src/carte.c -o obj/carte.o

obj/main.o: src/main.c include/interface.h
	gcc -Wall -Wextra -std=c99 -c src/main.c -o obj/main.o
