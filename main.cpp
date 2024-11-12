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

            float tEsfera = INFINITY, tChao = INFINITY, tFundo = INFINITY;
            bool intersecaoEsfera = esfera.intersecao(raio, tEsfera);
            bool intersecaoChao = chao.intersecao(raio, tChao);
            bool intersecaoFundo = fundo.intersecao(raio, tFundo);

            float tFinal = INFINITY;
            Vetor3D corFinal(0.0f, 0.0f, 0.0f);
            Vetor3D kd, ke, ka;
            int brilho;

            if (intersecaoEsfera && tEsfera < tFinal)
            {
                tFinal = tEsfera;
                kd = kdEsfera;
                ke = keEsfera;
                ka = kaEsfera;
                brilho = brilhoEsfera;
            }
            if (intersecaoChao && tChao < tFinal)
            {
                tFinal = tChao;
                kd = kdChao;
                ke = keChao;
                ka = kaChao;
                brilho = brilhoChao;
            }
            if (intersecaoFundo && tFundo < tFinal)
            {
                tFinal = tFundo;
                kd = kdFundo;
                ke = keFundo;
                ka = kaFundo;
                brilho = brilhoFundo;
            }

            if (tFinal < INFINITY)
            {
                Vetor3D pontoIntersecao = raio.origem + raio.direcao * tFinal;
                Vetor3D normalIntersecao = (tFinal == tEsfera) ? (pontoIntersecao - esfera.centro).normalize()
                                                               : (tFinal == tChao ? normalChao : normalFundo);

                Vetor3D direcaoLuz = (posicaoLuz - pontoIntersecao).normalize();
                Vetor3D direcaoVisao = -raio.direcao.normalize();
                Vetor3D luzRefletida = normalIntersecao * 2 * normalIntersecao.dot(direcaoLuz) - direcaoLuz;

                float intensidadeDifusa = std::max(0.0f, normalIntersecao.dot(direcaoLuz));
                float intensidadeEspecular = std::pow(std::max(0.0f, luzRefletida.dot(direcaoVisao)), brilho);

                Vetor3D corDifusa = kd * intensidadeLuz * intensidadeDifusa;
                Vetor3D corEspecular = ke * intensidadeLuz * intensidadeEspecular;
                Vetor3D corAmbiente = ka * intensidadeAmbiente;
                corFinal = corDifusa + corEspecular + corAmbiente;

                int r = std::min(255, std::max(0, static_cast<int>(corFinal.x * 255)));
                int g = std::min(255, std::max(0, static_cast<int>(corFinal.y * 255)));
                int b = std::min(255, std::max(0, static_cast<int>(corFinal.z * 255)));

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
