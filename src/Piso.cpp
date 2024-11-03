#include "Piso.h"

Piso::Piso(int largura, int profundidade, int seed, float tamanhoLadrilho)
    : largura(largura), profundidade(profundidade), seed(seed), tamanhoLadrilho(tamanhoLadrilho)
{
  // Define o canto esquerdo automaticamente com base no tamanho do piso e dos ladrilhos
  cantoEsquerdo = Ponto(-largura * tamanhoLadrilho / 2.0f, 0, -profundidade * tamanhoLadrilho / 2.0f);
}

void Piso::desenhaPiso()
{
  srand(seed); // Usa uma semente fixa para gerar sempre as mesmas cores no piso.
  glPushMatrix();
  glTranslated(cantoEsquerdo.x, cantoEsquerdo.y, cantoEsquerdo.z);

  // Desenha o piso usando as dimensões e tamanho dos ladrilhos definidos
  for (int x = 0; x < largura; x++)
  {
    glPushMatrix();
    for (int z = 0; z < profundidade; z++)
    {
      desenhaLadrilho(MediumGoldenrod, rand() % 40);
      glTranslated(0, 0, tamanhoLadrilho); // Move para o próximo ladrilho na direção Z
    }
    glPopMatrix();
    glTranslated(tamanhoLadrilho, 0, 0); // Move para o próximo ladrilho na direção X
  }
  glPopMatrix();
}

void Piso::desenhaLadrilho(int corBorda, int corDentro)
{
  defineCor(corDentro); // Define a cor de preenchimento.

  glBegin(GL_QUADS);
  glNormal3f(0, 1, 0);
  glVertex3f(-tamanhoLadrilho / 2.0f, 0.0f, -tamanhoLadrilho / 2.0f);
  glVertex3f(-tamanhoLadrilho / 2.0f, 0.0f, tamanhoLadrilho / 2.0f);
  glVertex3f(tamanhoLadrilho / 2.0f, 0.0f, tamanhoLadrilho / 2.0f);
  glVertex3f(tamanhoLadrilho / 2.0f, 0.0f, -tamanhoLadrilho / 2.0f);
  glEnd();

  defineCor(corBorda); // Define a cor da borda.

  glBegin(GL_LINE_STRIP);
  glNormal3f(0, 1, 0);
  glVertex3f(-tamanhoLadrilho / 2.0f, 0.0f, -tamanhoLadrilho / 2.0f);
  glVertex3f(-tamanhoLadrilho / 2.0f, 0.0f, tamanhoLadrilho / 2.0f);
  glVertex3f(tamanhoLadrilho / 2.0f, 0.0f, tamanhoLadrilho / 2.0f);
  glVertex3f(tamanhoLadrilho / 2.0f, 0.0f, -tamanhoLadrilho / 2.0f);
  glEnd();
}

void Piso::desenhaChao()
{
  // Desenha o piso com as dimensões especificadas (sem duplicação)
  desenhaPiso();
}
