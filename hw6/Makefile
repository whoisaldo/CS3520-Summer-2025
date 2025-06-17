# Makefile for Assignment 6 (Automatic Parking Lot + Object Pool)

# Compiler and flags
CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra -pedantic -pthread

# Default target
.PHONY: all
all: test_object_pool test_parking_system

# ObjectPool tests
test_object_pool: test_object_pool.cpp ObjectPool.hpp
	$(CXX) $(CXXFLAGS) -o $@ test_object_pool.cpp

# ParkingSystem tests
test_parking_system: Customer.cpp ParkingSystem.cpp Vehicle.cpp test_parking_system.cpp
	$(CXX) $(CXXFLAGS) -o $@ Customer.cpp ParkingSystem.cpp Vehicle.cpp test_parking_system.cpp

# Remove built artifacts
.PHONY: clean
clean:
	rm -f test_object_pool test_parking_system

