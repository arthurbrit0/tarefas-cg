#include <iostream>
#include <fstream>
#include <vector>
#include "funcs.h"

int main() {
    double wJanela = 1.0;                           // definindo a largura, altura e profundidade da janela
    double hJanela = 1.0;
    double dJanela = 1.0; 

    Ponto3D olho(0.0, 0.0, 0.0);                    // iniciando o olho do observador nas coordenadas 0,0,0

    double rEsfera = 0.5;                           // iniciando o raio da esfera como 0.5
    double zEsfera = - (dJanela + rEsfera + 1.0);   // iniciando a coordenada z da esfera como a soma da profundidade da janela, o raio da esfera e 1.0 (negativa pois está "antes" do observador)
    Ponto3D centroEsfera(0.0, 0.0, zEsfera);        // iniciando o centro da esfera nas coordenadas 0,0,zEsfera

    Color esfColor(255, 0, 0);                      // definindo a cor da esfera como vermelho
    Color bgColor(100, 100, 100);                   // definindo a cor de fundo como cinza

    int nCol = 800;                                 // definindo o número de colunas e linhas da imagem 
    int nLin = 800; 

    double Dx = wJanela / nCol;                     // definindo o tamanho de cada pixel
    double Dy = hJanela / nLin;

    std::vector<std::vector<Color>> image(nLin, std::vector<Color>(nCol, bgColor));  // criando a imagem com as dimensões definidas, com um array de arrays de cores

    for (int l = 0; l < nLin; l++) {
        for (int c = 0; c < nCol; c++) {
            double x = - wJanela / 2.0 + Dx / 2.0 + c * Dx;                          // para cada pixel da imagem, calcula-se a coordenada x, y e z do ponto correspondente
            double y =   hJanela / 2.0 - Dy / 2.0 - l * Dy;
            double z = -dJanela;

            Ponto3D pontoJanela(x, y, z);                                            // cada pixel da imagem é um ponto na janela, com suas respectivas coordenadas

            Ponto3D direcao = (pontoJanela - olho).normalizar();                     // a direção do raio é o vetor normalizado entre o olho e o ponto na janela. normalizamos para obter somente a direcao

            double t;                                                                // variável que armazenará o ponto de interseção do raio com a esfera
            bool intersecao = funcs::intersecaoEsfera(olho, direcao, centroEsfera, rEsfera, t); // verificando se há interseção entre a esfera e o raio do observador

            if (intersecao) {
                image[l][c] = esfColor;                                                         // se tiver interseção, cada pixel da interseção recebe a cor da esfera
            } else {
                image[l][c] = bgColor;                                                          // se não, cada pixel recebe a cor de fundo
            }
        }
    }

    std::ofstream ofs("output.ppm");                                                            // criando a imagem para o output
    ofs << "P3\n" << nCol << " " << nLin << "\n255\n";
    for (int l = 0; l < nLin; l++) {
        for (int c = 0; c < nCol; c++) {
            Color &col = image[l][c];
            ofs << col.r << " " << col.g << " " << col.b << " ";
        }
        ofs << "\n";
    }
    ofs.close();

    std::cout << "Imagem gerada: output.ppm\n";
    return 0;
}
