run.out: block.o display.o player.o main.o keyboardhandler.o bullet.o
	g++ -o run.out block.o bullet.o display.o player.o main.o keyboardhandler.o -lSDL2 -Wall -Werror

main.o: main.cpp block.h display.h player.h settings.h keyboardhandler.h
	g++ -c -o main.o main.cpp -lSDL2 -Wall -Werror

keyboardhandler.o: keyboardhandler.cpp keyboardhandler.h
	g++ -c -o keyboardhandler.o keyboardhandler.cpp -lSDL2 -Wall -Werror

bullet.o: bullet.cpp bullet.h
	g++ -c -o bullet.o bullet.cpp -lSDL2 -Wall -Werror

block.o: block.cpp block.h
	g++ -c -o block.o block.cpp -lSDL2 -Wall -Werror

display.o: display.cpp display.h block.h bullet.h
	g++ -c -o display.o display.cpp -lSDL2 -Wall -Werror

player.o: player.cpp player.h bullet.h
	g++ -c -o player.o player.cpp -lSDL2 -Wall -Werror

clean: 
	rm -f *.out *.o
