
cc = gcc
cflags = -g -Wall

sources = src/*.c
objects = $(sources:.c=.o)
target  = game_of_chance

$(target) : $(objects)
	$(cc) $(cflags) -o bin/$@ $^


.phony: clean
clean:
	@rm -f bin/$(target) $(objects) core



