CC=g++
CPPFLAGS=-g -std=c++0x
LDFLAGS=-lm
OBJS=$(patsubst %.cpp, %, $(wildcard *.cpp))

all: $(OBJS)

$(OBJS): % : %.o

clean:
	rm -rf $(OBJS) *.o

test:
	echo $(OBJS)
