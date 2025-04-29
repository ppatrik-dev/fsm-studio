# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.
LDFLAGS = 

# Source files
SRCS = MooreState.cpp \
       MooreStateFactory.cpp \
       MooreMachine.cpp \
       main.cpp

OBJS = $(SRCS:.cpp=.o)
TARGET = bin/moore_machine

# Main target
all: $(TARGET)

# Ensure output directory exists
$(shell mkdir -p bin)

# Linking
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleanup
clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf bin

.PHONY: all clean