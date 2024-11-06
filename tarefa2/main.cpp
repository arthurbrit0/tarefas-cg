#include "raylib.h"
#include "header.h"
#include <algorithm>


// definição das propriedades da cena
const float janelaWidth = 2.0f;
const float janelaHeight = 1.5f;
const float janelaDistance = 1.0f;
const Color corBackground = {100, 100, 100, 255};

// propriedades da esfera
const float raioEsfera = 1.0f;
const Vetor3D centroEsfera(0.0f, 0.0f, -(janelaDistance + raioEsfera));

// propriedades da tela
const int telaWidth = 800;
const int telaHeight = 600;

// criando uma fonte luminosa, utilizando a classe PontoLuminoso, definindo os valores de posicao e intensidade como os passados no parametros do metodo construtor
PontoLuminoso fonteLuz(Vetor3D(0.0f, 5.0f, 0.0f), Vetor3D(0.7f, 0.7f, 0.7f));

// definindo as propriedades da luz
const Vetor3D difusa(1.0f, 0.0f, 0.0f);
const Vetor3D especular(1.0f, 1.0f, 1.0f);
const float intensidade = 32.0f;

// função para renderizar a cena com a esfera
void renderScene(Esfera& esfera) {
    // definindo largura e altura de cada pixel
    float pixelWidth = janelaWidth / telaWidth;
    float pixelHeight = janelaHeight / telaHeight;

    // percorrendo cada pixel da tela e definindo sua coordenada
    for (int linha = 0; linha < telaHeight; linha++) {
        float yCoord = janelaHeight/2.0f - pixelHeight/2.0f - linha*pixelHeight;
        for (int col = 0; col< telaWidth; col++) {
            float xCoord = -janelaWidth/2.0f + pixelWidth/2.0f + col*pixelWidth;
            // definindo a coordenada do centro de cada pixel
            Vetor3D centroPixel(xCoord, yCoord, -janelaDistance);
            Raio raio(Vetor3D(0.0f, 0.0f, 0.0f), centroPixel);

            float tIntersecao = 1000.0f;
            if (esfera.intersecao(raio, tIntersecao)) {
                // conferindo se a esfera tem intersecao com o raio
                // se tiver, o ponto de intersecao sera calculada usando a formula abaixo
                Vetor3D pontoIntersecao = raio.origem + raio.direcao*tIntersecao;
                // normalizamos o vetor que aponta do centro da esfera ate o ponto de intersecao
                Vetor3D normalIntersec = (pontoIntersecao - esfera.centro).normalizar();
                // obtemos a direcao do observador a partir da normalizacao do raio de visao
                Vetor3D direcaoVisao = -raio.direcao.normalizar();
                // obtemos a direcao da luz a partir da normalizacao do vetor que aponta da fonte de luz ate o ponto de intersecao
                Vetor3D direcaoLuz = (fonteLuz.posicao - pontoIntersecao).normalizar();
                // obtemos o vetor de luz refletida
                Vetor3D luzRefletida = normalIntersec *2* normalIntersec.dot(direcaoLuz) - direcaoLuz;

                // criamos o vetor cor final, que sera a soma da cor difusa e da cor especular
                float intesidadeDifusa = std::max(0.0f, normalIntersec.dot(direcaoLuz));
                float intesidadeEspecular = std::pow(std::max(0.0f, luzRefletida.dot(direcaoVisao)), intensidade);

                Vetor3D corDifusa = difusa*fonteLuz.intensidade*intesidadeDifusa;
                Vetor3D corEspecular = especular*fonteLuz.intensidade*intesidadeEspecular;
                Vetor3D corFinal = corDifusa + corEspecular;

                int r = std::min(255, std::max(0, static_cast<int>(corFinal.x * 255)));
                int g = std::min(255, std::max(0, static_cast<int>(corFinal.y * 255)));
                int b = std::min(255, std::max(0, static_cast<int>(corFinal.z * 255)));

                // para cada pixel da tela, desenhamos esse pixel com sua cor, sua coordenada x e y e sua opacidade 

                DrawPixel(col, linha, Color{(unsigned char)r, (unsigned char)g, (unsigned char)b, 255});
            }
        }
    }
}

int main() {
    InitWindow(telaWidth, telaHeight, "Raytracer");
    SetTargetFPS(60);

    Esfera esfera(centroEsfera, raioEsfera);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(corBackground);

        renderScene(esfera);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
