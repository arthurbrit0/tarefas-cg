#include "funcs.h"                                                      // incluindo o arquivo de cabeçalho funcs.h
#include <cmath>
#include <algorithm>

Color::Color(int red, int green, int blue) {                            // implementando a classe Color, com o método construtor definindo o tom default como preto
    r = red;
    g = green;
    b = blue;
}

Ponto3D::Ponto3D(double xCoord, double yCoord, double zCoord) {         // implementando a classe Ponto3D, com o método construtor definindo as coordenadas default como (0, 0, 0)
    x = xCoord;
    y = yCoord;
    z = zCoord;
}

Ponto3D Ponto3D::operator+(const Ponto3D& ponto) const {                // definindo o método operator + para a classe Ponto3D
    return Ponto3D(x + ponto.x, y + ponto.y, z + ponto.z);              // uma operação de soma entre dois pontos retorna um novo ponto, com a soma dos componentes dos dois pontos
}

Ponto3D Ponto3D::operator-(const Ponto3D& ponto) const {                // definindo o método operator - para a classe Ponto3D
    return Ponto3D(x - ponto.x, y - ponto.y, z - ponto.z);              // uma operação de subtração entre dois pontos retorna um novo ponto, com a subtração dos componentes dos dois pontos
}

Ponto3D Ponto3D::operator*(double escalar) const {                      // definindo o método operator * para a classe Ponto3D
    return Ponto3D(x * escalar, y * escalar, z * escalar);              // uma operação de multiplicação de um ponto por um escalar retorna um novo ponto, com os componentes do ponto multiplicados pelo escalar   
}

double Ponto3D::escalar(const Ponto3D& ponto) const {                   // definindo o método escalar para a classe Ponto3D
    return x * ponto.x + y * ponto.y + z * ponto.z;                     // o método calcula o produto escalar entre dois pontos
}

Ponto3D Ponto3D::normalizar() const {                                   // definindo o método normalizar para a classe Ponto3D
    double norma = std::sqrt(x*x + y*y + z*z);                          // o método calcula a norma do ponto, que é definida como a raiz quadrada da soma dos quadrados dos componentes do ponto      
    return Ponto3D(x/norma, y/norma, z/norma);                          // o ponto normalizado é um novo ponto, com cada componente sendo dividido pela norma do ponto
}

bool funcs::intersecaoEsfera(const Ponto3D& origem, const Ponto3D& direcao, const Ponto3D& centroEsfera, double rEsfera, double& t) {
    Ponto3D oc = origem - centroEsfera;                                 // calculando o vetor OC, que é a diferença entre a origem do raio e o centro da esfera
    // norma = raiz(x do ponto ao quadrado + y do ponto ao quadrado + z do ponto ao quadrado) --> vetor normalizado é as componentes do vetor divididas pela norma
    double a = direcao.escalar(direcao);                                // calculando o quadrado da norma da direção do raio
    double b = 2.0 * oc.escalar(direcao);                               // calculando o produto escalar entre OC e a direção do raio
    double c = oc.escalar(oc) - rEsfera * rEsfera;                      // calculando o quadrado da norma de OC menos o quadrado do raio da esfera
    double delta = b * b - 4 * a * c;                                   // calculando o delta

    if (delta < 0) {                                                    // se o delta for negativo, não há interseção   
        return false; 
    }

    double sqrtDelta = std::sqrt(delta);                                // calculando a raiz de delta
    double t1 = (-b - sqrtDelta) / (2.0 * a);                           // calculando a primeira raiz da equação quadrática
    double t2 = (-b + sqrtDelta) / (2.0 * a);                           // calculando a segunda raiz da equação quadrática

    if (t1 > 0 && t2 > 0) {                                             // se existem duas raizes, há dois pontos de intersecao positivos, então pegamos o menor deles e armazenamos em t
        t = std::min(t1, t2);
    } else if (t1 > 0) {                                                // se só o t1 for maior que 0, armazenamos ele
        t = t1;
    } else if (t2 > 0) {                                                // se só o t2 for maior que 0, armazenamos ele
        t = t2;
    } else {                                                            // se nenhum dos dois for maior que 0, não há interseção positiva
        return false; 
    }

    return true; 
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
