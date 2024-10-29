#include "Player.h"
#include <cmath>

Player::Player(const Ponto &obs, const Ponto &vetorAlvo)
    : OBS(obs), VetorAlvo(vetorAlvo) {}

Ponto Player::getPosition() const
{
  return position;
}

void Player::setPosition(const Ponto &novaPosicao)
{
  position = novaPosicao;
}

void Player::setOBS(const Ponto &novoOBS)
{
  OBS = novoOBS;
}

void Player::setVetorAlvo(const Ponto &novoVetorAlvo)
{
  VetorAlvo = novoVetorAlvo;
}

void Player::updatePlayerPosition()
{
  float distanceFromCamera = 0.38f;
  position.x = OBS.x + VetorAlvo.x * distanceFromCamera;
  position.y = 0;
  position.z = OBS.z + VetorAlvo.z * distanceFromCamera;
}

void drawPayerBody(float length, float width, float height)
{
  glPushMatrix();
  glScalef(length, height, width);
  glutSolidCube(1.0);
  glPopMatrix();
}

void Player::drawPlayer()
{
  glPushMatrix();
  glTranslatef(position.x, -0.5f, position.z);

  float angle = atan2(VetorAlvo.z, VetorAlvo.x) * 180 / M_PI;
  glRotatef(-angle, 0, 1, 0);

  drawPayerBody(3.0f, 2.0f, 1.0f);

  glPopMatrix();
}
