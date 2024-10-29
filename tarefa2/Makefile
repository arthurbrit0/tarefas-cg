CXX = g++
CXXFLAGS = -I/usr/include/SDL2 -D_REENTRANT
LDFLAGS = -lSDL2

TARGET = raytracer

SRCS = functions.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
