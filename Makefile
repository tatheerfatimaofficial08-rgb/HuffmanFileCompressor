CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
TARGET   := main
SRCS     := main.cpp HuffmanEngine.cpp Node.cpp CompressionHistory.cpp
OBJS     := $(SRCS:.cpp=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
