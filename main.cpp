#include "raylib.h"
#include "header.h"
#include <algorithm>

// Definindo as propriedades da cena
const float larguraJanela = 60.0f;
const float alturaJanela = 60.0f;
const float distanciaJanela = 30.0f;
const int larguraCanvas = 500;
const int alturaCanvas = 500;

// Propriedades da esfera
const float raioEsfera = 40.0f;
const Vetor3D centroEsfera(0.0f, 0.0f, -100.0f);
const Vetor3D kdEsfera(0.7f, 0.2f, 0.2f);
const Vetor3D keEsfera(0.7f, 0.2f, 0.2f);
const Vetor3D kaEsfera(0.7f, 0.2f, 0.2f);
const int brilhoEsfera = 10;

// Propriedades do plano do chão
const Vetor3D pontoChao(0.0f, -raioEsfera, 0.0f);
const Vetor3D normalChao(0.0f, 1.0f, 0.0f);
const Vetor3D kdChao(0.2f, 0.7f, 0.2f);
const Vetor3D keChao(0.0f, 0.0f, 0.0f);
const Vetor3D kaChao(0.2f, 0.7f, 0.2f);
const int brilhoChao = 1;

// Propriedades do plano de fundo
const Vetor3D pontoFundo(0.0f, 0.0f, -200.0f);
const Vetor3D normalFundo(0.0f, 0.0f, 1.0f);
const Vetor3D kdFundo(0.3f, 0.3f, 0.7f);
const Vetor3D keFundo(0.0f, 0.0f, 0.0f);
const Vetor3D kaFundo(0.3f, 0.3f, 0.7f);
const int brilhoFundo = 1;

// Propriedades da luz
const Vetor3D intensidadeLuz(0.7f, 0.7f, 0.7f);
const Vetor3D posicaoLuz(0.0f, 60.0f, -30.0f);
const Vetor3D intensidadeAmbiente(0.3f, 0.3f, 0.3f);

void renderScene(Esfera &esfera, Plano &chao, Plano &fundo)
{
    float larguraPixel = larguraJanela / larguraCanvas;
    float alturaPixel = alturaJanela / alturaCanvas;

    for (int linha = 0; linha < alturaCanvas; linha++)
    {
        float yCoord = alturaJanela / 2.0f - alturaPixel / 2.0f - linha * alturaPixel;
        for (int coluna = 0; coluna < larguraCanvas; coluna++)
        {
            float xCoord = -larguraJanela / 2.0f + larguraPixel / 2.0f + coluna * larguraPixel;
            Vetor3D pontoPixel(xCoord, yCoord, -distanciaJanela);
            Raio raio(Vetor3D(0.0f, 0.0f, 0.0f), pontoPixel);

            // Reinicializar variáveis de interseção para o raio primário
            float tEsfera = INFINITY, tChao = INFINITY, tFundo = INFINITY;
            bool intersecaoEsfera = esfera.intersecao(raio, tEsfera);
            bool intersecaoChao = chao.intersecao(raio, tChao);
            bool intersecaoFundo = fundo.intersecao(raio, tFundo);

            float tFinal = INFINITY;
            Vetor3D corFinal(0.0f, 0.0f, 0.0f);
            Vetor3D kd, ke, ka;
            int brilho;
            Vetor3D normalIntersecao;

            if (intersecaoEsfera && tEsfera < tFinal)
            {
                tFinal = tEsfera;
                kd = kdEsfera;
                ke = keEsfera;
                ka = kaEsfera;
                brilho = brilhoEsfera;
                normalIntersecao = (raio.origem + raio.direcao * tEsfera - esfera.centro).normalize();
            }
            if (intersecaoChao && tChao < tFinal)
            {
                tFinal = tChao;
                kd = kdChao;
                ke = keChao;
                ka = kaChao;
                brilho = brilhoChao;
                normalIntersecao = normalChao;
            }
            if (intersecaoFundo && tFundo < tFinal)
            {
                tFinal = tFundo;
                kd = kdFundo;
                ke = keFundo;
                ka = kaFundo;
                brilho = brilhoFundo;
                normalIntersecao = normalFundo;
            }

            if (tFinal < INFINITY)
            {
                // calculando o ponto de intersecao do raio com o prox objeto
                Vetor3D pontoIntersecao = raio.origem + raio.direcao * tFinal;

                // calculando a direcao da visao do observador ate o ponto de inters
                Vetor3D direcaoVisao = -raio.direcao;

                // calculando o vetor que aponta para a luz partindo do ponto de intersecao
                Vetor3D l = (posicaoLuz - pontoIntersecao).normalize();

                // raio de sombra apontando para a posicao da luz (10 ^-4 para evitar intersecao com o mesmo objeto)
                Raio raioSombra(pontoIntersecao + normalIntersecao * 1e-4f, posicaoLuz);

                // verificando interseccao com a esfera para sombras no chao e fundo
                float tEsferaSombra = INFINITY;
                bool sombraEsfera = false;
                // se o objeto atual nao for a esfera, verificar se o raio da sombra intercepta
                if (tFinal != tEsfera)
                {
                    sombraEsfera = esfera.intersecao(raioSombra, tEsferaSombra);
                }

                // booleano para determinar se o ponto de intersecao esta em sombra
                bool emSombra = sombraEsfera && tEsferaSombra < (posicaoLuz-pontoIntersecao).norma();

                float intensidadeDifusa = 0.0f;
                float intensidadeEspecular = 0.0f;

                // se o ponto nao estiver em sombra, caculamos as intensidades difusa e especular
                if (!emSombra)
                {
                    intensidadeDifusa = std::max(0.0f, normalIntersecao.dot(l));
                    Vetor3D r = (normalIntersecao * 2 * normalIntersecao.dot(l) - l).normalize();
                    intensidadeEspecular = std::pow(std::max(0.0f, r.dot(direcaoVisao.normalize())), brilho);
                }

                // calculamos as componentes da cor ambiente
                Vetor3D corAmbiente = ka * intensidadeAmbiente;
                Vetor3D corFinal = corAmbiente;

                // se o ponto nao estiver em sombra, calculamos as componentes difusa e especular
                if (!emSombra)
                {
                    Vetor3D corDifusa = kd * intensidadeLuz * intensidadeDifusa;
                    Vetor3D corEspecular = ke * intensidadeLuz * intensidadeEspecular;
                    corFinal = corFinal + corDifusa + corEspecular; // Modificado para evitar o uso de +=
                }

                // Limitar as componentes de cor ao intervalo [0, 1]
                corFinal.x = std::min(1.0f, std::max(0.0f, corFinal.x));
                corFinal.y = std::min(1.0f, std::max(0.0f, corFinal.y));
                corFinal.z = std::min(1.0f, std::max(0.0f, corFinal.z));

                int r = static_cast<int>(corFinal.x * 255);
                int g = static_cast<int>(corFinal.y * 255);
                int b = static_cast<int>(corFinal.z * 255);

                DrawPixel(coluna, linha, Color{(unsigned char)r, (unsigned char)g, (unsigned char)b, 255});
            }
        }
    }
}

int main()
{
    InitWindow(larguraCanvas, alturaCanvas, "Raytracer");
    SetTargetFPS(60);

    Esfera esfera(centroEsfera, raioEsfera);
    Plano chao(pontoChao, normalChao);
    Plano fundo(pontoFundo, normalFundo);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        renderScene(esfera, chao, fundo);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
