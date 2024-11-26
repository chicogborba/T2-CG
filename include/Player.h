#ifndef PLAYER_H
#define PLAYER_H

#include "Ponto.h"
#include <cmath>

// Inclusão das bibliotecas necessárias dependendo do sistema operacional
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

#include <vector>
#include "Tiro.h"
#include "Modelo3D.h"
#include "PontosManager.h"

// Classe que representa o jogador no ambiente 3D
class Player
{
private:
  Ponto position;          // Posição atual do jogador
  Ponto OBS;               // Ponto de observação da câmera
  Ponto VetorAlvo;         // Vetor que indica a direção para onde o jogador está olhando
  float cannonAngle;       // Ângulo de rotação do canhão
  std::vector<Tiro> tiros; // Vetor de tiros disparados
  Modelo3D *modeloCorpo;

public:
  // Construtor da classe Player
  // @param obs Ponto de observação inicial
  // @param vetorAlvo Direção inicial do vetor alvo
  Player(const Ponto &obs, const Ponto &vetorAlvo);

  // Retorna a posição atual do jogador
  // @return Ponto representando a posição do jogador
  Ponto getPosition() const;

  // Define uma nova posição para o jogador
  // @param novaPosicao A nova posição a ser definida
  void setPosition(const Ponto &novaPosicao);

  // Define um novo ponto de observação (OBS)
  // @param novoOBS O novo ponto de observação
  void setOBS(const Ponto &novoOBS);

  // Define um novo vetor alvo (VetorAlvo)
  // @param novoVetorAlvo O novo vetor alvo
  void setVetorAlvo(const Ponto &novoVetorAlvo);

  // Atualiza a posição do jogador com base na câmera e vetor alvo
  void updatePlayerPosition();

  // Desenha o jogador na posição atual
  void drawPlayer();

  void raiseCannon(float angleIncrement);
  void lowerCannon(float angleDecrement);

  void dispararTiro(Ponto cameraAlvo); // Dispara um tiro na direção do alvo
  void updateTiros();                  // Atualiza todos os tiros

  std::vector<Tiro> getTiros() const { return tiros; };
};

#endif // PLAYER_H
