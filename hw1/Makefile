# Compiler and flags
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# All your hw1 source files
SRCS     = q1_debug.cpp \
           file1.cpp     \
           file2.cpp     \
           file3.cpp     \
           q2_compound.cpp \
           q3_stats.cpp    \
           q4_replace.cpp
PROGS    = $(SRCS:.cpp=)

.PHONY: all clean

# Default: build everything
all: $(PROGS)

# Pattern rule: <prog> from <prog>.cpp
%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Delete all executables and objects
clean:
	rm -f $(PROGS) *.o
