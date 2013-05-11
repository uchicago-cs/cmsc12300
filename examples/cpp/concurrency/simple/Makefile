ifeq ($(DEBUG),yes)
  OPTIMIZE_FLAG = -O0 -g -DDEBUG
else
  OPTIMIZE_FLAG = -O3
endif


BINS = 2threads 2threads-2 counter async
DEPS = $(OBJS:.o=.d)
CXX = g++
CXXFLAGS = -std=c++0x -Wall -MMD -MP $(OPTIMIZE_FLAG)
LDLIBS = -pthread -lrt

all: $(BINS)

%: %.cpp 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $< -o $@ $(LDLIBS)
		
%.d: %.cpp

clean:
	-rm -f $(BINS) *.d
	
-include $(DEPS)
