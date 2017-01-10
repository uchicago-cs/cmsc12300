CXX=g++
CFLAGS=--std=c++11 -Wall
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)

.DEFAULT: all
all: $(OBJS) frequentflyer.bin

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

%.bin: $(OBJS)
	$(CXX) $(OBJS) -o $@

.PHONY: clean
clean:
	rm -f *.o
	rm -f *.a
	rm -f *.bin
