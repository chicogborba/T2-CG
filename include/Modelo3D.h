// Modelo3D.h
#ifndef MODELO3D_H
#define MODELO3D_H

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
#include "TextureClass.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

class Modelo3D
{
public:
  // Construtor que recebe a posição inicial do modelo
  Modelo3D(float x = 0.0f, float y = 0.0f, float z = 0.0f,
           float escalaX = 1.0f, float escalaY = 1.0f, float escalaZ = 1.0f,
           float rotX = 0.0f, float rotY = 0.0f, float rotZ = 0.0f);

  // Métodos para manipulação do modelo
  void carregarModelo(const char *caminhoModelo);
  void carregarTextura(const char *caminhoTextura);
  void desenhar();

  void setColor(float r, float g, float b);

  // Métodos para manipulação da posição
  void setPosicao(float x, float y, float z);
  void setEscala(float x, float y, float z);
  void setRotacao(float x, float y, float z);

  // Getters para posição atual
  Ponto getPosicao() const { return posicao; }
  Ponto getEscala() const { return escala; }
  Ponto getRotacao() const { return rotacao; }

private:
  Ponto posicao;                // Posição do modelo no mundo
  Ponto escala;                 // Escala do modelo
  Ponto rotacao;                // Rotação do modelo em graus
  float colorR, colorG, colorB; // Cor do modelo
  GLuint idTextura;             // ID da textura do modelo

  // Aqui você pode adicionar a estrutura necessária para armazenar
  // os vértices, normais, coordenadas de textura, etc.
  std::vector<Ponto> vertices;
  std::vector<Ponto> normais;
  std::vector<std::pair<float, float>> coordTextura;
};

#endif // MODELO3D_H
