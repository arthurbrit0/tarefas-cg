TARGET = raytracer
OBJDIR = outputs

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

SRCS = main.cpp funcs.cpp
OBJS = $(patsubst %.cpp, $(OBJDIR)/%.o, $(SRCS))

all: $(TARGET) run

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJDIR) $(TARGET) output.ppm

.PHONY: all clean run
