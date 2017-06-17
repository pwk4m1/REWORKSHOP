
cc = gcc
cflags = -g -Wall -static

sources = src/*.c
objects = $(sources:.c=.o)
target  = track_me_if_you_will

$(target) : $(objects)
	$(cc) $(cflags) -o bin/$@ $^


.phony: clean
clean:
	@rm -f bin/$(target) $(objects) core



