game.out: 
	clang *.c -g -lSDL2 -lSDL2_ttf -o game.out

clean:
	rm -f *.out  
