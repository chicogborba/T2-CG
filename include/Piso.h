#ifndef PISO_H
#define PISO_H

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

class Piso
{
public:
  Piso(int largura, int profundidade, int seed = 100, float tamanhoLadrilho = 1.0f); // Novo parâmetro `tamanhoLadrilho`

  void desenhaPiso();
  void desenhaChao();

private:
  void desenhaLadrilho(int corBorda, int corDentro);

  Ponto cantoEsquerdo;
  int largura;
  int profundidade;
  int seed;
  float tamanhoLadrilho; // Variável para controlar o tamanho dos ladrilhos
};

#endif // PISO_H
