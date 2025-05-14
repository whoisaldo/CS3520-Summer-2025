# Directory for headers (none here)
IDIR = .

# Compiler and flags
CC     = g++
CFLAGS = -I$(IDIR) -std=c++17 -Wall -Wextra

# Output directory for objects (same as src)
ODIR   = .

# Libraries (none)
LIBS   =

# Source files and object names
_SRCS  = q1_debug.cpp file1.cpp file2.cpp file3.cpp q2_compound.cpp q3_stats.cpp q4_replace.cpp
_OBJS  = $(patsubst %.cpp,$(ODIR)/%.o,$(_SRCS))

# Pattern rule to compile .cpp → .o
$(ODIR)/%.o: %.cpp
<tab>$(CC) -c -o $@ $< $(CFLAGS)

# Default: build all executables
all: q1_debug file1 file2 file3 q2_compound q3_stats q4_replace

# Link rules
q1_debug: $(ODIR)/q1_debug.o
<tab>$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

file1:    $(ODIR)/file1.o
<tab>$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

file2:    $(ODIR)/file2.o
<tab>$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

file3:    $(ODIR)/file3.o
<tab>$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

q2_compound: $(ODIR)/q2_compound.o
<tab>$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

q3_stats: $(ODIR)/q3_stats.o
<tab>$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

q4_replace: $(ODIR)/q4_replace.o
<tab>$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
<tab>rm -f $(ODIR)/*.o q1_debug file1 file2 file3 q2_compound q3_stats q4_replace
