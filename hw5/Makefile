# Younes.al@northeastern.edu
# Ali Younes 6/3/2025
# Tleis.A@northeastern.edu
# Ali Tleis
# CS3520 course

CXX       := g++
CXXFLAGS  := -std=c++17 -Iinclude

SOURCES   := main.cpp \
             world.cpp \
             organism.cpp \
             ant.cpp \
             queenant.cpp \
             maleant.cpp \
             workerant.cpp \
             doodlebug.cpp \
             newposcandidate.cpp \
             worldstatus.cpp

TARGET    := predator-prey-simulator

.PHONY: all run clean

all: $(TARGET)

$(TARGET):
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)

