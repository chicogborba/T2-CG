// HUD.cpp
#include "Hud.h"

HUD::HUD()
{
  // Aqui você pode inicializar algo se necessário
}

HUD::~HUD()
{
  // Aqui você pode limpar recursos se necessário
}

void HUD::renderBitmapString(float x, float y, void *font, const char *string)
{
  // Posiciona o texto em coordenadas de tela
  glRasterPos2f(x, y);
  while (*string)
  {
    glutBitmapCharacter(font, *string);
    ++string;
  }
}

void HUD::draw()
{
  // Salva a matriz de projeção e muda para ortográfica
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();

  // Projeção ortográfica ajustada à janela
  gluOrtho2D(0, 800, 0, 600);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  // Desenha o texto no canto superior esquerdo
  glColor3f(1.0f, 1.0f, 1.0f); // Cor branca para o texto
  std::string pontosStr = "Pontos: " + std::to_string(PontosManager::getPontos());
  renderBitmapString(10, 580, GLUT_BITMAP_HELVETICA_18, pontosStr.c_str());

  std::string forcaStr = "Forca: " + std::to_string(PontosManager::getPontos());
  renderBitmapString(10, 560, GLUT_BITMAP_HELVETICA_18, forcaStr.c_str());

  // Restaura as matrizes de projeção e modelagem
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}
