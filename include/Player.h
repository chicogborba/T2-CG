#ifndef PLAYER_H
#define PLAYER_H

#include "Ponto.h"

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

class Player
{
private:
  Ponto position;
  Ponto OBS;
  Ponto VetorAlvo;

public:
  Player(const Ponto &obs, const Ponto &vetorAlvo);

  Ponto getPosition() const;
  void setPosition(const Ponto &novaPosicao);

  void setOBS(const Ponto &novoOBS);
  void setVetorAlvo(const Ponto &novoVetorAlvo);

  void updatePlayerPosition();
  void drawPlayer();
};

#endif
