// HUD.h
#ifndef HUD_H
#define HUD_H

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

#include <string>
#include <iostream>
#include "PontosManager.h" // Supondo que a classe PontosManager já esteja definida em outro lugar

class HUD
{
public:
  HUD();  // Construtor
  ~HUD(); // Destruidor

  // Método para desenhar o HUD
  void draw();

private:
  // Método auxiliar para desenhar o texto na tela
  void renderBitmapString(float x, float y, void *font, const char *string);
};

#endif // HUD_H
