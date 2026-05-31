
CC=g++

CFLAGS=-std=c++17 -I. -lm

DEPS = $(wildcard *.hpp)
objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: 	$(objects)
	$(CC) -o main $(objects) $(CFLAGS)


clean:
	rm *.o ; rm *~


cleanall:
	rm main ; rm *.o ; rm *~
