#include "Player.h"

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

// Função para desenhar o corpo do jogador (tanque)
void drawPlayerBody(float length, float width, float height)
{
  glPushMatrix();
  glScalef(length, height, width); // Escala o corpo do jogador
  glutSolidCube(1.0);              // Desenha um cubo sólido
  glPopMatrix();
}

void Player::raiseCannon(float angleIncrement)
{
  cannonAngle += angleIncrement; // Aumenta o ângulo do canhão
  if (cannonAngle > 50.0f)       // Limite superior
  {
    cannonAngle = 50.0f;
  }
}

void Player::lowerCannon(float angleDecrement)
{

  cannonAngle -= angleDecrement; // Diminui o ângulo do canhão
  if (cannonAngle < 6.0f)        // Limite inferior
  {
    cannonAngle = 6.0f;
  }
}

void Player::dispararTiro(Ponto cameraAlvo)
{
  printf("Disparando tiro\n");
  // Vetor direção baseado no vetor alvo
  Ponto direction = cameraAlvo;

  // Usa o ângulo do canhão para calcular a direção.y
  direction.y = tan(cannonAngle * M_PI / 180.0f) * 5.0f;

  // Cria um tiro na posição do jogador e na direção do vetor alvo
  Tiro tiro(position, direction, 1.2f);

  // Adiciona o tiro ao vetor de tiros
  tiros.push_back(tiro);

  // Se o número de tiros for maior que 10, remove o mais antigo
  if (tiros.size() > 10)
  {
    tiros.erase(tiros.begin()); // Remove o primeiro elemento (o mais antigo)
  }
}

void Player::updateTiros()
{
  // Se não houver tiros, não faça nada
  if (tiros.empty())
  {
    return;
  }
  for (auto &tiro : tiros)
  {
    tiro.updateTiro();
    tiro.drawTiro();
  }
}

// Função para desenhar o canhão do jogador
void drawPlayerCannon(float length, float width, float height)
{
  glPushMatrix();
  glColor3f(0.16f, 0.20f, 0.12f);  // Define a cor do jogador
  glScalef(length, height, width); // Escala o canhão
  glutSolidCube(1.0);              // Desenha um cubo sólido para o canhão
  glPopMatrix();
}

// Desenha o jogador na posição atual
void Player::drawPlayer()
{
  glPushMatrix();
  glColor3f(0.16f, 0.20f, 0.12f);
  glTranslatef(position.x, -0.5f, position.z);

  float angle = atan2(VetorAlvo.z, VetorAlvo.x) * 180 / M_PI;
  glRotatef(-angle, 0, 1, 0);

  drawPlayerBody(3.0f, 2.0f, 1.0f);

  // Posiciona o canhão em cima do corpo do tanque
  glPushMatrix();
  glTranslatef(1.5f, 0.6f, 0.0f); // Ajusta a posição do canhão

  // Desloca o centro de rotação para o ponto desejado dentro do canhão
  glTranslatef(-2.0f, 0.0f, 0.0f); // Desloca o centro de rotação para cima (por exemplo)

  // Rotaciona o canhão em torno do novo centro
  glRotatef(cannonAngle, 0, 0, 1); // Rotaciona em torno do eixo X
  glTranslatef(2.0f, 0.0f, 0.0f);  // Ajusta a posição do canhão

  // Agora desenhe o canhão na nova posição
  drawPlayerCannon(4.0f, 0.5f, 0.5f);

  glPopMatrix();
  glPopMatrix();
}
