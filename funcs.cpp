#include "header.h"

Vetor3D::Vetor3D(float xCoord, float yCoord, float zCoord) : x(xCoord), y(yCoord), z(zCoord) {}

Vetor3D Vetor3D::operator+(const Vetor3D &v) const
{
    return Vetor3D(x + v.x, y + v.y, z + v.z);
}

Vetor3D Vetor3D::operator-(const Vetor3D &v) const
{
    return Vetor3D(x - v.x, y - v.y, z - v.z);
}

Vetor3D Vetor3D::operator*(float s) const
{
    return Vetor3D(x * s, y * s, z * s);
}

Vetor3D Vetor3D::operator*(const Vetor3D &v) const
{
    return Vetor3D(x * v.x, y * v.y, z * v.z);
}

Vetor3D Vetor3D::operator-() const
{
    return Vetor3D(-x, -y, -z);
}

float Vetor3D::dot(const Vetor3D &v) const
{
    return x * v.x + y * v.y + z * v.z;
}

float Vetor3D::norma() const
{
    return std::sqrt(this->dot(*this));
}

Vetor3D Vetor3D::normalize() const
{
    float norma = this->norma();
    return Vetor3D(x / norma, y / norma, z / norma);
}

Raio::Raio(Vetor3D origemVetor, Vetor3D extremidadeVetor) : origem(origemVetor)
{
    Vetor3D dir = extremidadeVetor - origem;
    direcao = dir.normalize();
}

Esfera::Esfera(Vetor3D centro_, float raio_) : centro(centro_), raio(raio_) {}

bool Esfera::intersecao(const Raio &r, float &t) const
{
    Vetor3D oc = r.origem - centro;
    float a = r.direcao.dot(r.direcao);
    float b = 2.0f * r.direcao.dot(oc);
    float c = oc.dot(oc) - this->raio * this->raio; // Usando this->raio para o raio da esfera
    float discriminante = b * b - 4 * a * c;

    if (discriminante < 0)
    {
        return false;
    }
    else
    {
        float sqrt_discriminante = sqrt(discriminante);
        float t0 = (-b - sqrt_discriminante) / (2.0f * a);
        float t1 = (-b + sqrt_discriminante) / (2.0f * a);

        if (t0 > t1)
        {
            std::swap(t0, t1);
        }

        if (t0 > 1e-4f && t0 < t)
        {
            t = t0;
            return true;
        }
        if (t1 > 1e-4f && t1 < t)
        {
            t = t1;
            return true;
        }
    }
    return false;
}

PontoLuminoso::PontoLuminoso(Vetor3D posicao_, Vetor3D intensidade_) : posicao(posicao_), intensidade(intensidade_) {}

Plano::Plano(Vetor3D p0_, Vetor3D normal_)
    : p0(p0_), normal(normal_.normalize()) {}

bool Plano::intersecao(const Raio &r, float &t) const
{
    float denom = r.direcao.dot(normal);
    if (std::abs(denom) > 1e-6)
    {
        Vetor3D p0l0 = p0 - r.origem;
        float tPlano = p0l0.dot(normal) / denom;
        if (tPlano > 1e-4f && tPlano < t)
        {
            t = tPlano;
            return true;
        }
    }
    return false;
}
