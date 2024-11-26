#include "Paredao.h"
#include <cstdlib>
#include <iostream>

/**
 * @brief Construtor da classe Paredao.
 *
 * @param largura Largura do paredão (em cubos 1x1x1).
 * @param altura Altura do paredão (em cubos 1x1x1).
 * @param posicao Posição do canto inferior esquerdo do paredão.
 * @param seed Semente para a geração de cores.
 */
Paredao::Paredao(int largura, int altura, Ponto posicao, int seed)
    : largura(largura), altura(altura), posicao(posicao), seed(seed)
{
  cubos.resize(largura, std::vector<Cubo>(altura)); // Inicializa os cubos
}

/**
 * @brief Desenha o paredão.
 */
void Paredao::desenhaParedao()
{
  srand(seed);
  glPushMatrix();
  glTranslated(posicao.x, posicao.y, posicao.z);

  for (int x = 0; x < largura; x++)
  {
    glPushMatrix();
    for (int y = 0; y < altura; y++)
    {
      if (!cubos[x][y].quebrado)
      {
        // Divida a textura em um número de quadrados
        int numTilesX = 50; // Número de tiles horizontais (por exemplo, 10x10)
        int numTilesY = 25; // Número de tiles verticais (por exemplo, 10x10)

        // Calcular as coordenadas de textura para o cubo
        float texCoordX = (float)(x % numTilesX) / numTilesX;
        float texCoordY = (float)(y % numTilesY) / numTilesY;

        // Desenha o cubo usando a parte da textura correspondente
        desenhaCubo(MediumGoldenrod, texCoordX, texCoordY, 1.0f / numTilesX, 1.0f / numTilesY);
      }
      glTranslated(0, 1.0f, 0);
    }
    glPopMatrix();
    glTranslated(1.0f, 0, 0);
  }
  glPopMatrix();
}

/**
 * @brief Desenha um polígono quadrado (cubo) com coordenadas de textura.
 */
void Paredao::desenhaCubo(int corBorda, float texCoordX, float texCoordY, float texWidth, float texHeight)
{
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, idTextura); // Vincula a textura carregada

  glDisable(GL_CULL_FACE); // Desativa o culling para desenhar ambos os lados

  GLfloat vertices[6][4][3] = {
      {// Frente
       {-0.5f, -0.5f, 0.5f},
       {0.5f, -0.5f, 0.5f},
       {0.5f, 0.5f, 0.5f},
       {-0.5f, 0.5f, 0.5f}},
      {// Traseira
       {0.5f, -0.5f, -0.5f},
       {0.5f, 0.5f, -0.5f},
       {-0.5f, 0.5f, -0.5f},
       {-0.5f, -0.5f, -0.5f}},
      {// Topo
       {-0.5f, 0.5f, 0.5f},
       {-0.5f, 0.5f, -0.5f},
       {0.5f, 0.5f, -0.5f},
       {0.5f, 0.5f, 0.5f}},
      {// Base
       {-0.5f, -0.5f, 0.5f},
       {0.5f, -0.5f, 0.5f},
       {0.5f, -0.5f, -0.5f},
       {-0.5f, -0.5f, -0.5f}},
      {// Esquerda
       {-0.5f, -0.5f, 0.5f},
       {-0.5f, 0.5f, 0.5f},
       {-0.5f, 0.5f, -0.5f},
       {-0.5f, -0.5f, -0.5f}},
      {// Direita
       {0.5f, -0.5f, 0.5f},
       {0.5f, -0.5f, -0.5f},
       {0.5f, 0.5f, -0.5f},
       {0.5f, 0.5f, 0.5f}}};

  GLfloat texCoords[6][4][2] = {
      {// Frente
       {texCoordX, texCoordY},
       {texCoordX + texWidth, texCoordY},
       {texCoordX + texWidth, texCoordY + texHeight},
       {texCoordX, texCoordY + texHeight}},
      {// Traseira
       {texCoordX, texCoordY},
       {texCoordX + texWidth, texCoordY},
       {texCoordX + texWidth, texCoordY + texHeight},
       {texCoordX, texCoordY + texHeight}},
      {// Topo
       {texCoordX, texCoordY},
       {texCoordX + texWidth, texCoordY},
       {texCoordX + texWidth, texCoordY + texHeight},
       {texCoordX, texCoordY + texHeight}},
      {// Base
       {texCoordX, texCoordY},
       {texCoordX + texWidth, texCoordY},
       {texCoordX + texWidth, texCoordY + texHeight},
       {texCoordX, texCoordY + texHeight}},
      {// Esquerda
       {texCoordX, texCoordY},
       {texCoordX + texWidth, texCoordY},
       {texCoordX + texWidth, texCoordY + texHeight},
       {texCoordX, texCoordY + texHeight}},
      {// Direita
       {texCoordX, texCoordY},
       {texCoordX + texWidth, texCoordY},
       {texCoordX + texWidth, texCoordY + texHeight},
       {texCoordX, texCoordY + texHeight}}};

  glBegin(GL_QUADS);

  // Loop para desenhar todas as faces do cubo
  for (int i = 0; i < 6; i++)
  {
    // Desenha a face
    for (int j = 0; j < 4; j++)
    {
      glNormal3f(vertices[i][j][0], vertices[i][j][1], vertices[i][j][2]);
      glTexCoord2f(texCoords[i][j][0], texCoords[i][j][1]);
      glVertex3f(vertices[i][j][0], vertices[i][j][1], vertices[i][j][2]);
    }
  }

  glEnd();

  glEnable(GL_CULL_FACE); // Reativa o culling

  glDisable(GL_TEXTURE_2D);
}

void Paredao::detectarColisao(Ponto objetoPosicao)
{
  // utiliza o x,y e z de cada do cubo pra verificar a colisão

  // loop sobre a lista de cubos pra ver se o objeto colidiu com algum

  for (int x = 0; x < largura; x++)
  {
    for (int y = 0; y < altura; y++)
    {
      if (!cubos[x][y].quebrado)
      {
        // Verifica se o objeto colidiu com o cubo
        if (objetoPosicao.x >= posicao.x + x - 0.5 && objetoPosicao.x <= posicao.x + x + 0.5 &&
            objetoPosicao.y >= posicao.y + y - 0.5 && objetoPosicao.y <= posicao.y + y + 0.5 &&
            objetoPosicao.z >= posicao.z - 0.5 && objetoPosicao.z <= posicao.z + 0.5)
        {
          // Marca o cubo como quebrado
          // cubos[x][y].quebrado = true;

          // Quebra todos os cubos adjacentes em um raio de 1 ou seja 3x3
          for (int i = -1; i <= 1; i++)
          {
            for (int j = -1; j <= 1; j++)
            {
              if (x + i >= 0 && x + i < largura && y + j >= 0 && y + j < altura)
              {
                cubos[x + i][y + j].quebrado = true;
                PontosManager::adicionarPontos(5);
              }
            }
          }

          std::cout << "Cubo quebrado: " << x << " " << y << std::endl;
        }
      }
    }
  }
}

void Paredao::carregarTextura(const char *caminho)
{
  idTextura = LoadTexture(caminho);
  if (idTextura == (GLuint)-1)
  {
    std::cerr << "Erro ao carregar a textura do paredão: " << caminho << std::endl;
    exit(1);
  }
}
