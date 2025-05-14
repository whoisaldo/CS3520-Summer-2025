CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# List all your hw1 source files here
ALL_SRCS = q1_debug.cpp file1.cpp file2.cpp file3.cpp
ALL_PROGS = $(ALL_SRCS:.cpp=)

# Default target: build all programs
all: $(ALL_PROGS)

# Pattern rule: compile each .cpp into an executable of the same name
%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Clean up generated executables
clean:
	rm -f $(ALL_PROGS)
