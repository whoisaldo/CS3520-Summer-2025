# Makefile for Convention Center Management System

CXX      := g++
CXXFLAGS := -std=c++17 -Iinclude -Wall -Wextra -g
LDLIBS   := -lstdc++fs

SRCDIR   := src
BUILDDIR := build
BINDIR   := bin
TARGET   := management_system

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS  := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
DEPENDS  := $(OBJECTS:.o=.d)

.PHONY: all clean help

# Default target: build the executable
all: $(BINDIR)/$(TARGET)

# Link rule: create bin/management_system from object files
$(BINDIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LDLIBS)

# Compile rule: build each .o from its .cpp and generate dependencies
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Include dependency files if they exist
-include $(DEPENDS)

# Remove build artifacts
clean:
	rm -rf $(BUILDDIR) $(BINDIR)

# Show help message
help:
	@echo "Usage:"
	@echo "  make        Build the project"
	@echo "  make clean  Remove build artifacts"

