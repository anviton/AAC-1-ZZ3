CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGET = postier_chinois
SRCS = main.cpp graph.cpp file_reader.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = graph.h file_reader.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
