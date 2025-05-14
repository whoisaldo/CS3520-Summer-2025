# Compiler and flags
CXX       = g++
CXXFLAGS  = -std=c++17 -Wall -Wextra

# List all your source files here
SRCS      = q1_debug.cpp file1.cpp file2.cpp file3.cpp q2_compound.cpp q3_stats.cpp q4_replace.cpp
PROGS     = $(SRCS:.cpp=)

.PHONY: all clean

# Default target: build every executable
all: $(PROGS)

# Pattern rule: each program is built from its .cpp
%: %.cpp
<TAB>$(CXX) $(CXXFLAGS) $< -o $@

# Remove all executables and object files
clean:
<TAB>rm -f $(PROGS) *.o
