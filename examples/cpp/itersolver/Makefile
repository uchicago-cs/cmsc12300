OBJS = Solver.o JacobiSolver.o LinearEquations.o main.o
OBJSNOOPT = $(OBJS:.o=.no.o)
DEPS = $(OBJS:.o=.d)
CC = g++
CXXFLAGS = -Wall -MMD -MP
BIN = jacobi jacobi-noopt

all: jacobi jacobi-noopt

jacobi: CXXFLAGS += -O3
jacobi-noopt: CXXFLAGS += -O0 -g3

jacobi: $(OBJS)
	$(CC) $(LDFLAGS) $(LDLIBS) $(OBJS) -o jacobi

jacobi-noopt: $(OBJSNOOPT)
	$(CC) $(LDFLAGS) $(LDLIBS) $(OBJSNOOPT) -o jacobi-noopt
	
%.no.o: %.cpp
	$(CC) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@
	
%.d: %.cpp


clean:
	-rm -f $(OBJS) $(OBJS:.o=.no.o) $(BIN) *.d
	
-include $(DEPS)
