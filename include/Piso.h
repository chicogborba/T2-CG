#ifndef PISO_H
#define PISO_H

// Inclusão de bibliotecas de acordo com o sistema operacional
#ifdef WIN32
#include <windows.h>
#include <glut.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <GL/glut.h>
#endif

#include "Ponto.h"
#include "ListaDeCoresRGB.h"
#include "Player.h"
#include "KeyboardController.h"
#include "TextureClass.h"

/**
 * @brief Classe que representa um piso.
 *
 * A classe é responsável por desenhar um piso composto por ladrilhos
 * com dimensões específicas e um sistema de cores gerado aleatoriamente.
 */
class Piso
{
public:
  GLuint idTextura; // Identificador da textura do piso

  /**
   * @brief Construtor da classe Piso.
   *
   * Inicializa um piso com largura, profundidade, semente e tamanho do ladrilho.
   *
   * @param largura Largura do piso em ladrilhos.
   * @param profundidade Profundidade do piso em ladrilhos.
   * @param seed Semente para a geração de cores. O padrão é 100.
   * @param tamanhoLadrilho Tamanho de cada ladrilho. O padrão é 1.0f.
   */
  Piso(int largura, int profundidade, int seed = 100, float tamanhoLadrilho = 1.0f);

  /**
   * @brief Desenha o piso.
   *
   * Utiliza a semente para gerar cores e desenha ladrilhos em uma grade.
   */
  void desenhaPiso();

  /**
   * @brief Desenha o chão.
   *
   * Método para desenhar o piso sem duplicação de lógica.
   */
  void desenhaChao();

  /**
   * @brief Carrega uma textura para o piso.
   *
   * @param caminho Caminho para a textura a ser carregada.
   */
  void carregarTextura(const char *caminho);

private:
  /**
   * @brief Desenha um ladrilho.
   *
   * Define as cores de preenchimento e borda e desenha o ladrilho como um quadrado.
   *
   * @param corBorda Cor da borda do ladrilho.
   * @param corDentro Cor interna do ladrilho.
   */
  void desenhaLadrilho(int corBorda, int corDentro);

  Ponto cantoEsquerdo;   ///< Ponto que representa o canto esquerdo do piso.
  int largura;           ///< Largura do piso em ladrilhos.
  int profundidade;      ///< Profundidade do piso em ladrilhos.
  int seed;              ///< Semente para geração de cores.
  float tamanhoLadrilho; ///< Tamanho de cada ladrilho.
};

#endif // PISO_H
