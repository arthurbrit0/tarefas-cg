#ifndef HEADER_H
#define HEADER_H

#include <cmath>
#include <algorithm>

// Classe Vetor3D
class Vetor3D
{
public:
    float x, y, z;
    Vetor3D(float xCoord = 0, float yCoord = 0, float zCoord = 0);
    Vetor3D operator+(const Vetor3D &v) const;
    Vetor3D operator-(const Vetor3D &v) const;
    Vetor3D operator*(float s) const;
    Vetor3D operator*(const Vetor3D &v) const;
    Vetor3D operator-() const;
    float dot(const Vetor3D &v) const;
    float norma() const;
    Vetor3D normalize() const;
};

// Classe Raio
class Raio
{
public:
    Vetor3D origem, direcao;
    Raio(Vetor3D origemVetor, Vetor3D extremidadeVetor);
};

// Classe Esfera
class Esfera
{
public:
    Vetor3D centro;
    float raio;
    Esfera(Vetor3D centro_, float raio_);
    bool intersecao(const Raio &raio, float &t) const;
};

// Classe Plano
class Plano
{
public:
    Vetor3D p0;     // Um ponto conhecido no plano
    Vetor3D normal; // Vetor normal unitário ao plano

    // Construtor do Plano que normaliza o vetor normal
    Plano(Vetor3D p0_, Vetor3D normal_);

    // Função para verificar a interseção com o raio
    bool intersecao(const Raio &raio, float &t) const;
};

// Classe PontoLuminoso
class PontoLuminoso
{
public:
    Vetor3D posicao, intensidade;
    PontoLuminoso(Vetor3D posicao_, Vetor3D intensidade_);
};

#endif
