#include "Player.h"
#include <cmath>

// Construtor da classe Player
Player::Player(const Ponto &obs, const Ponto &vetorAlvo)
    : OBS(obs), VetorAlvo(vetorAlvo) {}

// Retorna a posição atual do jogador
Ponto Player::getPosition() const
{
  return position;
}

// Define uma nova posição para o jogador
// @param novaPosicao A nova posição a ser definida
void Player::setPosition(const Ponto &novaPosicao)
{
  position = novaPosicao;
}

// Define um novo ponto de observação (OBS)
// @param novoOBS O novo ponto de observação
void Player::setOBS(const Ponto &novoOBS)
{
  OBS = novoOBS;
}

// Define um novo vetor alvo (VetorAlvo)
// @param novoVetorAlvo O novo vetor alvo
void Player::setVetorAlvo(const Ponto &novoVetorAlvo)
{
  VetorAlvo = novoVetorAlvo;
}

// Atualiza a posição do jogador com base na câmera e vetor alvo
void Player::updatePlayerPosition()
{
  const float distanceFromCamera = 0.38f; // Distância do jogador em relação à câmera
  position.x = OBS.x + VetorAlvo.x * distanceFromCamera;
  position.y = 0; // Mantém a altura constante
  position.z = OBS.z + VetorAlvo.z * distanceFromCamera;
}

// Desenha o corpo do jogador com as dimensões especificadas
// @param length Comprimento do corpo do jogador
// @param width Largura do corpo do jogador
// @param height Altura do corpo do jogador
void drawPlayerBody(float length, float width, float height)
{
  glPushMatrix();
  glScalef(length, height, width); // Escala o corpo do jogador
  glutSolidCube(1.0);              // Desenha um cubo sólido
  glPopMatrix();
}

// Desenha o jogador na posição atual
void Player::drawPlayer()
{
  glPushMatrix();
  glTranslatef(position.x, -0.5f, position.z); // Move o jogador para a posição correta

  // Calcula o ângulo de rotação baseado no vetor alvo
  float angle = atan2(VetorAlvo.z, VetorAlvo.x) * 180 / M_PI;
  glRotatef(-angle, 0, 1, 0); // Rotaciona o jogador

  drawPlayerBody(3.0f, 2.0f, 1.0f); // Desenha o corpo do jogador

  glPopMatrix();
}
