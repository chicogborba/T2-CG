#ifndef PAREDAO_H
#define PAREDAO_H

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

#include <cstdlib>
#include <iostream>
#include <vector>

#include "Ponto.h"
#include "ListaDeCoresRGB.h"
#include "TextureClass.h"

struct Cubo
{
  bool quebrado = false; // Indica se o cubo está quebrado
};

/**
 * @brief Classe que representa um paredão.
 *
 * A classe é responsável por desenhar um paredão composto por cubos de 1x1,
 * com dimensões específicas e uma posição definida.
 */
class Paredao
{
public:
  GLuint idTextura; ///< Identificador da textura do paredão

  /**
   * @brief Construtor da classe Paredao.
   *
   * Inicializa um paredão com largura, altura e posição.
   *
   * @param largura Largura do paredão (em cubos).
   * @param altura Altura do paredão (em cubos).
   * @param posicao Posição do canto inferior esquerdo do paredão.
   * @param seed Semente para a geração de cores. O padrão é 100.
   */
  Paredao(int largura, int altura, Ponto posicao, int seed = 100);

  /**
   * @brief Desenha o paredão.
   *
   * Desenha o paredão na posição especificada.
   */
  void desenhaParedao();

  /**
   * @brief Detecta a colisão de um objeto com o paredão.
   *
   * @param objetoPosicao Posição do objeto a ser verificada.
   */
  void detectarColisao(Ponto objetoPosicao);

  /**
   * @brief Carrega uma textura para os cubos do paredão.
   *
   * @param caminho Caminho para a textura a ser carregada.
   */
  void carregarTextura(const char *caminho);

private:
  /**
   * @brief Desenha um cubo na posição atual.
   *
   * Define as cores de preenchimento e desenha o cubo.
   *
   * @param corBorda Cor da borda do cubo.
   * @param corDentro Cor interna do cubo.
   */
  void desenhaCubo(int corBorda, int corDentro);

  Ponto posicao;                        ///< Posição do canto inferior esquerdo do paredão.
  std::vector<std::vector<Cubo>> cubos; ///< Matriz de cubos que compõem o paredão
  int largura;                          ///< Largura do paredão (em cubos).
  int altura;                           ///< Altura do paredão (em cubos).
  int seed;                             ///< Semente para geração de cores.
};

#endif // PAREDAO_H
