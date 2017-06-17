
cc = gcc
cflags = -g -Wall

sources = src/*.c
objects = $(sources:.c=.o)
target  = readme_if_you_can_lol

$(target) : $(objects)
	$(cc) $(cflags) -o bin/$@ $^


.phony: clean
clean:
	@rm -f bin/$(target) $(objects) core



