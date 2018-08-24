src = $(wildcard *.c)
obj = $(src:.c=.o)

LDFLAGS = -g -Wall -Werror -lSDL2 -lSDL2_image -lSDL2_ttf 

game.out: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(obj) game.out
