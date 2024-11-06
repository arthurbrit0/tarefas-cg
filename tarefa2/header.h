#ifndef HEADER_H
#define HEADER_H
#include <cmath>

class Vetor3D {                                                            // classe para definicao do vetor e suas coordenadas
public:
    float x;
    float y;
    float z;
    Vetor3D(float xCoord = 0, float yCoord = 0, float zCoord = 0);         // construtor da classe, definindo as coordenadas default do vetor como 0 (sera implementada no funcs.cpp)
    Vetor3D operator+(const Vetor3D& v) const;                             // criando operador de soma entre o vetor this e o vetor v, retornando um novo vetor
    Vetor3D operator-(const Vetor3D& v) const;                             // criando operador de subtracao entre o vetor this e o vetor v, retornando um novo vetor   
    Vetor3D operator*(float s) const;                                      // criando operador de multiplicacao entre o vetor this e um escalar s, retornando um novo vetor
    Vetor3D operator*(const Vetor3D& v) const;                             // criando operador de produto entre vetores, retornando um novo vetor
    Vetor3D operator-() const;                                             // criando operador de negacao do vetor this, retornando um novo vetor
    float dot(const Vetor3D& v) const;                                     // criando funcao para calcular o produto escalar entre o vetor this e o vetor v        
    float norma() const;                                                   // funcao para calcular a norma do vetor this (comprimento)
    Vetor3D normalizar() const;                                            // funcao para normalizar o vetor this (comprimento = 1), obtendo a direcao do vetor
};

class Raio {
public:
    Vetor3D origem;
    Vetor3D direcao;
    Raio(Vetor3D origemVetor, Vetor3D extremidade);
};
class Esfera {
public:
    Vetor3D centro;
    float raio;
    Esfera(Vetor3D centroEsfera, float raioEsfera);
    bool intersecao(const Raio &raioEsfera, float &t) const;
};
class PontoLuminoso {
public:
    Vetor3D posicao;
    Vetor3D intensidade;
    PontoLuminoso(Vetor3D posicaoPL, Vetor3D intensidadePL);
};

#endif
