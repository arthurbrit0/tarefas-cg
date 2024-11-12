#include "header.h"

Vetor3D::Vetor3D(float xCoord, float yCoord, float zCoord) : x(xCoord), y(yCoord), z(zCoord) {} // inicialziando os valores de x, y e z com os valores passados na lista de inicialziacao

Vetor3D Vetor3D::operator+(const Vetor3D &v) const
{
    return Vetor3D(x + v.x, y + v.y, z + v.z); // implementando a soma entre dois vetores, que retorna um vetor com a soma de cada componente
};

Vetor3D Vetor3D::operator-(const Vetor3D &v) const
{
    return Vetor3D(x - v.x, y - v.y, z - v.z); // implementando a subtracao entre dois vetores, que retorna um vetor com a subtracao de cada componente
};

Vetor3D Vetor3D::operator*(float s) const
{
    return Vetor3D(x * s, y * s, z * s); // implementando a mult de um vetor por um escalar, que retorna um vetor  com cada componente multiplicada por esse escalar
};

Vetor3D Vetor3D::operator*(const Vetor3D &v) const
{
    return Vetor3D(x * v.x, y * v.y, z * v.z); // implementando a multiplicao de um vetor por outro vetor, que retorna um novo vetor com as componentes sendo o resultado da mult entre as
}; // componentes de cada vetor
Vetor3D Vetor3D::operator-() const
{ // implementando a negacao de um vetor, retornando um novo vetor com as componentes negativas do original
    return Vetor3D(-x, -y, -z);
};

float Vetor3D::dot(const Vetor3D &v) const
{                                       // implementando o produto escalar entre dois vetores, retornando um float
    return x * v.x + y * v.y + z * v.z; // a soma dos produtos das componentes de cada vetor
};

float Vetor3D::norma() const
{                                       // implementando a funcao para calcular a norma de um vetor, retornando um float
    return std::sqrt(this->dot(*this)); // a raiz quadrada do produto escalar do vetor com ele mesmo
};

Vetor3D Vetor3D::normalize() const
{                                                    // implementando a funcao para normalizar um vetor, ou seja, deixa-lo unitario
    float norma = this->norma();                     // calculando a norma do vetor
    return Vetor3D(x / norma, y / norma, z / norma); // dividindo cada componente do vetor pela norma, obtendo um vetor unitario
};

Raio::Raio(Vetor3D origemVetor, Vetor3D extremidadeVetor) : origem(origemVetor)
{                                            // implementando a funcao construtora da classe Raio, definindo o valor da origem como o vetor origemVetor
    Vetor3D dir = extremidadeVetor - origem; // o vetor direção é a extremidade do vetor - sua origem
    direcao = dir.normalize();               // para obter apenas a direção, sem nos importarmos com o comprimento, normalizamos o vetor direcao (tornamos-o unitario)
}

Esfera::Esfera(Vetor3D centro_, float raio_) : centro(centro_), raio(raio_) {} // implementando a funcao construtora da classe Esfera, que definira os valores do centro e raio como os passados como parametro no construtor

bool Esfera::intersecao(const Raio &raio, float &t) const
{                                                   // implementando a funcao para verificar se há intersecao entre a esfera e o raio
    Vetor3D OC = raio.origem - centro;              // calculando o vetor OC, que é o vetor que aponta da origem do raio ate o centro da esfera
    float a = raio.direcao.dot(raio.direcao);       // fazendo o produto escalar do vetor direcao do raio com ele mesmo
    float b = 2 * raio.direcao.dot(OC);             // fazendo o produto escalar do vetor direcao do raio com o vetor v
    float c = OC.dot(OC) - this->raio * this->raio; // fazendo o produto escalar do OC com ele mesmo e subtraindo o quadrado do raio da esfera
    float delta = b * b - 4 * a * c;                // calculando o delta

    if (delta > 0)
    { // se o delta for maior que 0, há intersecao
        float t1 = (-b + std::sqrt(delta)) / (2.0f * a);
        float t2 = (-b - std::sqrt(delta)) / (2.0f * a);
        float t_atual = std::fmin(t1, t2); // armazenamos o menor valor entre as duas raizes
        if (t_atual > 0 && t_atual < t)
        { // validando se essa raiz realmente esta no intervalo de interesse
            t = t_atual;
            return true;
        }
    }
    else if (delta == 0)
    {                               // se o delta for igual a 0, há intersecao tangencial
        float t1 = -b / (2.0f * a); // fórmula para calcular a unica raiz
        if (t1 > 0 && t1 < t)
        { // validando se essa raiz realmente esta no intervalo de interesse
            t = t1;
            return true;
        }
    }
    return false; // se não houver intersecao, retornamos false
}

// criando um ponto luminoso, definindo os valores de posicao e intensidade como os passados no parametros do metodo construtor
PontoLuminoso::PontoLuminoso(Vetor3D posicao_, Vetor3D intensidade_) : posicao(posicao_), intensidade(intensidade_) {}

Plano::Plano(Vetor3D p0_, Vetor3D normal_)
    : p0(p0_), normal(normal_.normalize()) {}

// interseção entre o raio e o plano
bool Plano::intersecao(const Raio &raio, float &t) const
{
    float denom = raio.direcao.dot(normal); // Calcula o denominador, que é o produto escalar entre a direção do raio e a normal do plano
    if (std::abs(denom) > 1e-6)
    {                                    // Verifica se o denominador não é próximo de zero, o que significaria que o raio é paralelo ao plano
        Vetor3D p0l0 = p0 - raio.origem; // Vetor do ponto no plano até a origem do raio
        t = p0l0.dot(normal) / denom;    // Calcula a distância da origem do raio ao ponto de interseção
        return t >= 0;                   // Retorna verdadeiro se o ponto de interseção estiver à frente do ponto de origem do raio
    }
    return false; // Se o denominador for zero, não há interseção válida
}

// ::: EXPLICAÇÃO DA FORMULA DA ESFERA :::
/*
    Equação do raio = P(t) = VetorOrigem + t * VetorDirecao, onde VetorOrigem é o ponto de partida do raio, VetorDirecao é o vetor direção do raio, e t é o
    parâmetro que representa a distância percorrida ao longo do vetor direção (quanto maior t, mais distante do ponto de partida o raio está).

    Qualquer ponto P~ na superfície da esfera satisfaz a seguinte condição:
    | P~ - centroEsfera~| ^ 2 = raioEsfera ^ 2.

    Para saber se o raio tem interseção com a esfera, substituios a fórmula do raio no P da fórmula da esfera, ficando com o seguinte:
    | VetorOrigem + t * VetorDirecao - centroEsfera | ^ 2 = raioEsfera ^ 2.

    Definimos OC como o vetor que vai do centro da esfera até a origem do raio (OC = VetorOrigem - centroEsfera), e substituímos na fórmula anterior:
    | OC + t * VetorDirecao | ^ 2 = raioEsfera ^ 2.

    Expandimos a fórmula anterior, obtendo o seguinte:

    (OC + t * VetorDirecao) . (OC + t * VetorDirecao) = raioEsfera ^ 2, resultando em:

    OC . OC + 2*t* OC . VetorDirecao + t^2 *VetorDirecao . VetorDirecao = raioEsfera ^ 2.

    Podemos rearranjar essa fórmula em função de t.

    Teremos uma equação quadrática do tipo: a*t^2 + b*t + c = 0, onde:

    t^2(VetorDirecao . VetorDirecao) + 2t(OC . VetorDirecao) + (OC . OC - raioEsfera^2) = 0, com
    a = VetorDirecao . VetorDirecao,
    b = 2 * OC . VetorDirecao,
    c = OC . OC - raioEsfera^2.

    Assim, se o delta da equação quadrática é negativo, não há interseção. Se o delta é = 0, há uma interseção tangencial. Se o delta é positivo, há duas interseções.
*/