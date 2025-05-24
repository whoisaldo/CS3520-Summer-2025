# Younes.al@northeastern.edu
# Ali Younes 5/23/2025 CS3520 course

# Compiler and flags
CC       = g++
CFLAGS   = -std=c++11 -Wall -g -O0

# If you need ncurses, uncomment the next line
# LIBS   = -lncurses
LIBS     =

# Source files and corresponding object files
SRC      = 2d_dynamic.cpp  \
           3dmatrix.cpp    \
           charptr.cpp     \
           practice_1.cpp  \
           practice_2.cpp  \
           struct.cpp

OBJ      = $(SRC:.cpp=.o)

# Executable names (one per source)
TARGETS  = 2d_dynamic  \
           3dmatrix    \
           charptr     \
           practice_1  \
           practice_2  \
           struct

# Default target builds all executables
all: $(TARGETS)

# Link each .o into its executable
$(TARGETS): %: %.o
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

# Compile .cpp files into .o
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up binaries and objects
.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGETS)

