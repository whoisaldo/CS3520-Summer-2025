# hw4/Makefile

CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra

TARGET := teambuilder
SRCS := main.cpp TeamBuilder.cpp
OBJS := $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp TeamBuilder.hpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)

