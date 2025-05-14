# Directory for headers (none used here)
IDIR = .

# Compiler and flags
CC     = g++
CFLAGS = -I$(IDIR) -std=c++17 -Wall -Wextra

# Output directory for object files (same as src)
ODIR   = .

# Libraries (none needed)
LIBS   =

# Dependencies (none)
_DEPS =
DEPS  = $(patsubst %,$(IDIR)/%,$(_DEPS))

# Object file names
_OBJ1 = file1.o
_OBJ2 = file2.o
_OBJ3 = file3.o
_OBJ4 = q2_compound.o
_OBJ5 = q4_replace.o
_OBJ6 = q3_stats.o
_OBJ7 = q1_debug.o

# Pattern rule: compile each .cpp into .o
$(ODIR)/%.o: %.cpp $(DEPS)
<tab>$(CC) -c -o $@ $< $(CFLAGS)

# Default target builds all executables
all: q1_debug file1 file2 file3 q2_compound q3_stats q4_replace

# Link each executable
q1_debug: $(_OBJ7)
<tab>$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

file1: $(_OBJ1)
<tab>$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

file2: $(_OBJ2)
<tab>$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

file3: $(_OBJ3)
<tab>$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

q2_compound: $(_OBJ4)
<tab>$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

q3_stats: $(_OBJ6)
<tab>$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

q4_replace: $(_OBJ5)
<tab>$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
<tab>rm -f *~ core $(IDIR)/*~ 
<tab>rm -f q1_debug file1 file2 file3 q2_compound q3_stats q4_replace
<tab>rm -f *.o

etags:
<tab>find . -type f -iname "*.[ch]" | xargs etags --append
