# Nome do executável
TARGET = raytracer

# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Bibliotecas
LDFLAGS = -lraylib -lm

# Arquivos fonte e objetos
SRCS = main.cpp funcs.cpp
OBJS = main.o funcs.o

# Regra principal
all: $(TARGET)

# Regra para construir o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Regra para compilar main.o
main.o: main.cpp header.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# Regra para compilar funcs.o
funcs.o: funcs.cpp header.h
	$(CXX) $(CXXFLAGS) -c funcs.cpp -o funcs.o

# Limpeza dos arquivos compilados
clean:
	rm -f $(OBJS) $(TARGET)

# Regra para rodar o programa
run: $(TARGET)
	./$(TARGET)
