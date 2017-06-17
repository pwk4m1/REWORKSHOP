
cc = gcc
cflags = -g -Wall -s -static

sources = src/*.c
objects = $(sources:.c=.o)
target  = crack_me

$(target) : $(objects)
	$(cc) $(cflags) -o bin/$@ $^

.phony: clean
clean:
	@rm -f bin/$(target) $(objects) core



