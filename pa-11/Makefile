# Makefile for PA11 MyString program

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = mystring
SRC = mystring.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

clean:
	rm -f $(TARGET)

