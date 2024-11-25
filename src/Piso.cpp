#include "Piso.h"

/**
 * @brief Construtor da classe Piso.
 *
 * Inicializa um piso com largura, profundidade, semente e tamanho do ladrilho.
 *
 * @param largura Largura do piso em ladrilhos.
 * @param profundidade Profundidade do piso em ladrilhos.
 * @param seed Semente para a geração de cores.
 * @param tamanhoLadrilho Tamanho de cada ladrilho.
 */
Piso::Piso(int largura, int profundidade, int seed, float tamanhoLadrilho)
    : largura(largura), profundidade(profundidade), seed(seed), tamanhoLadrilho(tamanhoLadrilho)
{
  // Define o canto esquerdo automaticamente com base no tamanho do piso e dos ladrilhos
  cantoEsquerdo = Ponto(-largura * tamanhoLadrilho / 2.0f, 0, -profundidade * tamanhoLadrilho / 2.0f);
}

/**
 * @brief Desenha o piso.
 *
 * Utiliza a semente para gerar cores e desenha ladrilhos em uma grade.
 */
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

/**
 * @brief Desenha um ladrilho.
 *
 * Define as cores de preenchimento e borda e desenha o ladrilho como um quadrado.
 *
 * @param corBorda Cor da borda do ladrilho.
 * @param corDentro Cor interna do ladrilho.
 */
void Piso::desenhaLadrilho(int corBorda, int corDentro)
{
  // Reseta qualquer cor que estava antes
  glColor3f(1.0f, 1.0f, 1.0f);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, idTextura); // Vincula a textura carregada

  glBegin(GL_QUADS);
  glNormal3f(0, 1, 0);

  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-tamanhoLadrilho / 2.0f, 0.0f, -tamanhoLadrilho / 2.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-tamanhoLadrilho / 2.0f, 0.0f, tamanhoLadrilho / 2.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(tamanhoLadrilho / 2.0f, 0.0f, tamanhoLadrilho / 2.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(tamanhoLadrilho / 2.0f, 0.0f, -tamanhoLadrilho / 2.0f);

  glEnd();

  glDisable(GL_TEXTURE_2D);

  // // Desenhe a borda (opcional, sem textura)
  // defineCor(corBorda);
  // glBegin(GL_LINE_STRIP);
  // glNormal3f(0, 1, 0);
  // glVertex3f(-tamanhoLadrilho / 2.0f, 0.0f, -tamanhoLadrilho / 2.0f);
  // glVertex3f(-tamanhoLadrilho / 2.0f, 0.0f, tamanhoLadrilho / 2.0f);
  // glVertex3f(tamanhoLadrilho / 2.0f, 0.0f, tamanhoLadrilho / 2.0f);
  // glVertex3f(tamanhoLadrilho / 2.0f, 0.0f, -tamanhoLadrilho / 2.0f);
  // glEnd();
}

void Piso::carregarTextura(const char *caminhoTextura)
{
  idTextura = LoadTexture(caminhoTextura);
  if (idTextura == (GLuint)-1)
  {
    std::cerr << "Erro ao carregar a textura do piso: " << caminhoTextura << std::endl;
    exit(1);
  }
}

/**
 * @brief Desenha o chão.
 *
 * Método para desenhar o piso sem duplicação de lógica.
 */
void Piso::desenhaChao()
{
  desenhaPiso(); // Desenha o piso com as dimensões especificadas
}
