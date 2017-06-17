
cc = gcc
cflags = -g -Wall

sources = src/*.c
objects = $(sources:.c=.o)
target  = strings_are_nice

$(target) : $(objects)
	$(cc) $(cflags) -o bin/$@ $^


.phony: clean
clean:
	@rm -f bin/$(target) $(objects) core



