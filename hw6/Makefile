# Makefile for Assignment 6 (hw6/)
# ---------------------------------
CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra -pedantic -pthread -Iinclude

SRC_DIR   := src
INC_DIR   := include

# Executables
POOL_EXE  := test_object_pool
PS_EXE    := test_parking_system

# Source files
POOL_SRCS := $(SRC_DIR)/test_object_pool.cpp
PS_SRCS   := \
	$(SRC_DIR)/test_parking_system.cpp \
	$(SRC_DIR)/Customer.cpp \
	$(SRC_DIR)/ParkingSystem.cpp \
	$(SRC_DIR)/Vehicle.cpp

.PHONY: all clean

all: $(POOL_EXE) $(PS_EXE)

# ObjectPool tests
$(POOL_EXE): $(POOL_SRCS) $(INC_DIR)/ObjectPool.hpp
	$(CXX) $(CXXFLAGS) -o $@ $(POOL_SRCS)

# ParkingSystem tests
$(PS_EXE): $(PS_SRCS) \
           $(INC_DIR)/Customer.hpp \
           $(INC_DIR)/ParkingSystem.hpp \
           $(INC_DIR)/Vehicle.hpp
	$(CXX) $(CXXFLAGS) -o $@ $(PS_SRCS)

clean:
	rm -f $(POOL_EXE) $(PS_EXE)

