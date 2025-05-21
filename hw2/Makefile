# Compiler and flags
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g

# Executable name
TARGET   := airline

# Source and object files
SRCS     := part2b.cpp
OBJS     := $(SRCS:.cpp=.o)

# Phony targets (not real files)
.PHONY: all clean

# Default target
all: $(TARGET)

# Link step
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile step (pattern rule)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(TARGET) $(OBJS)

