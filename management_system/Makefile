# Makefile for Convention Center Management System

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Iinclude -Wall -Wextra -g

# Directories
SRCDIR := src
INCDIR := include
BUILDDIR := build
BINDIR := bin

# Executable name
TARGET := management_system

# Source and object files
tmp_SOURCES := $(wildcard $(SRCDIR)/*.cpp)
SOURCES := $(tmp_SOURCES)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
DEPENDS := $(OBJECTS:.o=.d)

# Phony targets
.PHONY: all clean help

# Default build target
default: all

all: $(BINDIR)/$(TARGET)

# Link step
$(BINDIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile step with dependency generation
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Include header dependencies
-include $(DEPENDS)

# Clean up build artifacts
clean:
	rm -rf $(BUILDDIR) $(BINDIR)

# Help message
help:
	@echo "Usage:"
	@echo "  make        Build the project"
	@echo "  make clean  Remove build artifacts"

