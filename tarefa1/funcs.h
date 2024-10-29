#ifndef FUNCS_H                                                             // definindo FUNCS_H para evitar problemas de duplicação na compilação
#define FUNCS_H
#include <cmath>

class Color {                                                               // classe Color, que representará o tom de cor de cada pixel, com atriutos r, g e b
public:
    int r;
    int g;
    int b;
    Color(int red=0, int green=0, int blue=0);                              // método construtor da classe Color, definindo o tom default como preto
};

class Ponto3D {                                                             // classe Ponto3D, que representará as coordenadas de cada ponto no espaço tridimensional, com atributos x, y e z
public:
    double x, y, z;
    Ponto3D(double xCoord=0, double yCoord=0, double zCoord=0);             // método construtor da classe Ponto3D, definindo as coordenadas default como (0, 0, 0) 

    Ponto3D operator+ (const Ponto3D& ponto) const;                         // operador de soma entre dois pontos
    Ponto3D operator- (const Ponto3D& ponto) const;                         // operador de subtração entre dois pontos
    Ponto3D operator* (double escalar) const;                               // operador de multiplicação de um ponto por um escalar
    double escalar (const Ponto3D& ponto) const;                            // método que calcula o produto escalar entre dois pontos
    Ponto3D normalizar () const;                                            // método que normaliza um ponto
};

class funcs {
public:                                                                     // método que verifica se há interseção entre um raio e uma esfera
    static bool intersecaoEsfera(const Ponto3D& origem, const Ponto3D& direcao, const Ponto3D& centroEsfera, double rEsfera, double& t);
};

#endif // FUNCS_H
