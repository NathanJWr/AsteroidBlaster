game.out: 
	clang *.c -lSDL2 -lSDL2_ttf -o game.out

clean:
	rm -f *.out  
