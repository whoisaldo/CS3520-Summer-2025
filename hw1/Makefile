# Compiler settings
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# All source files
SRCS     = q1_debug.cpp file1.cpp file2.cpp file3.cpp q2_compound.cpp q3_stats.cpp q4_replace.cpp
PROGS    = $(SRCS:.cpp=)

.PHONY: all clean

# Default: build all executables
all: $(PROGS)

# Build any program from its .cpp
%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Remove everything we built
clean:
	rm -f $(PROGS) *.o
