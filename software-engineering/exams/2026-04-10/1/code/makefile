
CC=g++

CFLAGS=-std=c++17 -I. -lm -O2

ifeq ($(DEBUG), 1)
CFLAGS += -DDEBUG -g
endif

ifeq ($(OPT),1)
CFLAGS += -O1
endif
ifeq ($(OPT),2)
CFLAGS += -O2
endif
ifeq ($(OPT),3)
CFLAGS += -O3
endif
ifeq ($(OPT),4)
CFLAGS += -O3 -Ofast -funroll-loops -flto -march=native
endif

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
