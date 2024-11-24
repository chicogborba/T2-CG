#include "Paredao.h"
#include <cstdlib>
#include <iostream>

/**
 * @brief Construtor da classe Paredao.
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
        desenhaCubo(MediumGoldenrod, rand() % 40);
      }
      glTranslated(0, 1.0f, 0);
    }
    glPopMatrix();
    glTranslated(1.0f, 0, 0);
  }
  glPopMatrix();
}

/**
 * @brief Desenha um polígono quadrado.
 */
void Paredao::desenhaCubo(int corBorda, int corDentro)
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
       {0.0f, 0.0f},
       {1.0f, 0.0f},
       {1.0f, 1.0f},
       {0.0f, 1.0f}},
      {// Traseira
       {0.0f, 0.0f},
       {1.0f, 0.0f},
       {1.0f, 1.0f},
       {0.0f, 1.0f}},
      {// Topo
       {0.0f, 0.0f},
       {1.0f, 0.0f},
       {1.0f, 1.0f},
       {0.0f, 1.0f}},
      {// Base
       {0.0f, 0.0f},
       {1.0f, 0.0f},
       {1.0f, 1.0f},
       {0.0f, 1.0f}},
      {// Esquerda
       {0.0f, 0.0f},
       {1.0f, 0.0f},
       {1.0f, 1.0f},
       {0.0f, 1.0f}},
      {// Direita
       {0.0f, 0.0f},
       {1.0f, 0.0f},
       {1.0f, 1.0f},
       {0.0f, 1.0f}}};

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

  // Desenhe a borda (opcional, sem textura)
  // defineCor(corBorda);
  // glBegin(GL_LINE_LOOP);
  // glVertex3f(-0.5f, -0.5f, 0.5f);
  // glVertex3f(-0.5f, 0.5f, 0.5f);
  // glVertex3f(0.5f, 0.5f, 0.5f);
  // glVertex3f(0.5f, -0.5f, 0.5f);
  // glEnd();
}

void Paredao::detectarColisao(Ponto objetoPosicao)
{
  int x = objetoPosicao.x - posicao.x;
  int y = objetoPosicao.y - posicao.y;

  if (x >= 0 && x < largura && y >= 0 && y < altura)
  {
    cubos[x][y].quebrado = true; // Marca o cubo como quebrado
  }
}

/**
 * @brief Carrega a textura do paredão.
 */
void Paredao::carregarTextura(const char *caminho)
{
  idTextura = LoadTexture(caminho);
  if (idTextura == (GLuint)-1)
  {
    std::cerr << "Erro ao carregar a textura do paredão: " << caminho << std::endl;
    exit(1);
  }
}
