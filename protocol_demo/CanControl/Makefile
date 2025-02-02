CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2

SRCS = controlDemo.cpp ../Common/socketWrap.cpp

HEADERS = ../Common/socketWrap.hpp

OBJS = $(SRCS:.cpp=.o)

TARGET = ControlDemo

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)