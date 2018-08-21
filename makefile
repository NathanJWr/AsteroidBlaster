game.out: 
	gcc -std=c99 *.c -Wall -Werror -lSDL2 -lSDL2_ttf -lSDL2_image -o game.out

clean:
	rm -f *.out *.h.gch 
