# Compiler and flags
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g

# Target executable
TARGET   := airline

# Source files
SRCS     := part2b.cpp

# Default rule
all: $(TARGET)

# Link/compile
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Remove built files
clean:
	rm -f $(TARGET) *.o

.PHONY: all clean

