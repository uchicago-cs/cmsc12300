ifeq ($(DEBUG),yes)
  OPTIMIZE_FLAG = -O0 -g -DDEBUG
else
  OPTIMIZE_FLAG = -O3
endif


OBJS = Minefield.o
CXX = g++
CXXFLAGS = -std=c++0x -Wall -MMD -MP $(OPTIMIZE_FLAG)
LDLIBS = -pthread -lrt
BINS = rmine fieldgen
DEPS = $(OBJS:.o=.d) $(BINS:=.d)

all: $(BINS)

rmine: $(OBJS) rmine.o
	$(CXX) $(LDFLAGS) $(OBJS) rmine.o -o rmine $(LDLIBS)

fieldgen: $(OBJS) fieldgen.o
	$(CXX) $(LDFLAGS) $(OBJS) fieldgen.o -o fieldgen $(LDLIBS)
		
%.d: %.cpp

clean:
	-rm -f $(OBJS) $(BINS:=.o) $(BINS) *.d
	
-include $(DEPS)
