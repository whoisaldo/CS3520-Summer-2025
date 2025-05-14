CC      = g++
CFLAGS  = -std=c++17 -Wall -Wextra

ALL_SRCS  = q1_debug.cpp file1.cpp file2.cpp file3.cpp q2_compound.cpp q3_stats.cpp q4_replace.cpp
ALL_PROGS = $(ALL_SRCS:.cpp=)

# Default target: build all executables
all: $(ALL_PROGS)

# Pattern rule: compile each .cpp into an executable of the same name
%: %.cpp
<TAB>$(CC) $(CFLAGS) $< -o $@

# Remove all generated files
clean:
<TAB>rm -f $(ALL_PROGS) *.o
