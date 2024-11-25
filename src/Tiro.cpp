#include "Tiro.h"

// Construtor da classe Tiro
Tiro::Tiro(const Ponto &startPos, const Ponto &target, float speed, float initialVerticalSpeed)
    : position(startPos), speed(speed), initialVerticalSpeed(initialVerticalSpeed)
{
  // Calcula a direção normalizada
  float dx = target.x - startPos.x;
  float dy = target.y - startPos.y;
  float dz = target.z - startPos.z;

  float magnitude = sqrt(dx * dx + dy * dy + dz * dz);

  if (magnitude != 0)
  {
    direction.x = dx / magnitude;
    direction.y = dy / magnitude;
    direction.z = dz / magnitude;
  }
}

void Tiro::updateTiro()
{

  // printf("initialSpeed: %f\n", initialVerticalSpeed);
  // printf("speed: %f\n", speed);
  // Atualiza a posição do tiro na direção
  position.x += direction.x * speed;
  initialVerticalSpeed -= 0.003f;

  position.y += direction.y * initialVerticalSpeed;
  position.z += direction.z * speed;

  // Aplica o efeito da gravidade (reduzindo o y)
  // position.y -= 0.08f;
}

// Desenha o tiro na posição atual
void Tiro::drawTiro() const
{
  glPushMatrix();
  glPushAttrib(GL_CURRENT_BIT); // Salva o estado atual, incluindo a cor

  glColor3f(1.0f, 0.0f, 0.0f); // Define a cor do tiro (vermelho)
  glTranslatef(position.x, position.y, position.z);
  glScalef(0.2f, 0.2f, 0.2f); // Escala o cubo para que seja pequeno
  glutSolidCube(1.0);         // Desenha um cubo sólido

  glPopAttrib(); // Restaura o estado anterior, incluindo a cor
  glPopMatrix();
}

// Retorna a posição atual do tiro
Ponto Tiro::getPosition() const
{
  return position;
}

// Define uma nova posição para o tiro
void Tiro::setPosition(const Ponto &novaPosicao)
{
  position = novaPosicao;
}
