
cc = gcc
cflags = -g -Wall

sources = src/*.c
objects = $(sources:.c=.o)
target  = crack_me_ez_one

$(target) : $(objects)
	$(cc) $(cflags) -o bin/$@ $^


.phony: clean
clean:
	@rm -f bin/$(target) $(objects) core



