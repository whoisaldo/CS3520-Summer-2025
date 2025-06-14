# Makefile for PA-12 Debug Tasks

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Compile each debug file
debug_t-1: debug_t-1.cpp
	$(CXX) $(CXXFLAGS) debug_t-1.cpp -o debug_t-1

debug_t-2: debug_t-2.cpp
	$(CXX) $(CXXFLAGS) debug_t-2.cpp -o debug_t-2

debug_t-3: debug_t-3.cpp
	$(CXX) $(CXXFLAGS) debug_t-3.cpp -o debug_t-3

debug_t-4: debug_t-4.cpp
	$(CXX) $(CXXFLAGS) debug_t-4.cpp -o debug_t-4

debug_t-5: debug_t-5.cpp
	$(CXX) $(CXXFLAGS) debug_t-5.cpp -o debug_t-5

# Run all compiled programs
run: debug_t-1 debug_t-2 debug_t-3 debug_t-4 debug_t-5
	./debug_t-1
	./debug_t-2
	./debug_t-3
	./debug_t-4
	./debug_t-5

# Clean up executables
clean:
	rm -f debug_t-1 debug_t-2 debug_t-3 debug_t-4 debug_t-5

