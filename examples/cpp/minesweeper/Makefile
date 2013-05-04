ifeq ($(DEBUG),yes)
  OPTIMIZE_FLAG = -O0 -g -DDEBUG
else
  OPTIMIZE_FLAG = -O3
endif


OBJS = Minefield.o rmine.o
DEPS = $(OBJS:.o=.d)
CXX = g++
CXXFLAGS = -std=c++0x -Wall -MMD -MP $(OPTIMIZE_FLAG)
BIN = rmine
LDLIBS = -pthread -lrt

all: $(BIN)

$(BIN): $(OBJS) 
	$(CXX) $(LDFLAGS) $(OBJS) -o $(BIN) $(LDLIBS)
		
%.d: %.cpp

clean:
	-rm -f $(OBJS) $(BIN) *.d
	
-include $(DEPS)
