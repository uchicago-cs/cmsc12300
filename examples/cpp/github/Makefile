ifeq ($(DEBUG),yes)
  OPTIMIZE_FLAG = -O0 -g -DDEBUG
else
  OPTIMIZE_FLAG = -O3
endif


OBJS = GitHubActivityReader.o GitHubActivityFileReader.o \
       GitHubActivityEvent.o \
       jsoncpp.o main.o 
DEPS = $(OBJS:.o=.d)
CXX = g++
CXXFLAGS = -std=c++0x -Wall -MMD -MP -I. $(OPTIMIZE_FLAG)
LDLIBS = -lrt -lboost_iostreams
BIN = github-events 

all: github-events

$(BIN): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(BIN) $(LDLIBS)
		
%.d: %.cpp

clean:
	-rm -f $(OBJS) $(BIN) *.d
	
-include $(DEPS)
