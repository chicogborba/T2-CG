#ifndef TIRO_H
#define TIRO_H

#include "Ponto.h"
#include <cmath>

// Inclusão das bibliotecas necessárias para renderização
#ifdef WIN32
#include <windows.h>
#include <glut.h>
#elif defined(__APPLE__)
#include <GLUT/glut.h>
#elif defined(__linux__)
#include <GL/glut.h>
#else
#include <sys/time.h>
#endif

// Classe que representa um tiro
class Tiro
{
private:
  Ponto position;  // Posição atual do tiro
  Ponto direction; // Direção do tiro (normalizada)
  float speed;     // Velocidade do tiro
  float initialVerticalSpeed;
  // float time;                             // Tempo decorrido desde o disparo
  // static constexpr float GRAVITY = 9.81f; // Aceleração da gravidade

public:
  // Construtor da classe Tiro
  // @param startPos Posição inicial do tiro
  // @param target Alvo do tiro, usado para calcular a direção
  // @param speed Velocidade do tiro
  Tiro(const Ponto &startPos, const Ponto &target, float speed, float initialVerticalSpeed);

  // Atualiza a posição do tiro
  void updateTiro();

  // Desenha o tiro na posição atual
  void drawTiro() const;

  // Retorna a posição atual do tiro
  Ponto getPosition() const;

  // Define uma nova posição para o tiro
  void setPosition(const Ponto &novaPosicao);
};

#endif // TIRO_H
