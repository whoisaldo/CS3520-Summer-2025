# Makefile for Ali's PA13 version
CXX = g++
CXXFLAGS = -std=c++17 -pthread

TARGET = fib_runner
SRC = fib_runner.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

