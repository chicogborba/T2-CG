#include "Camera.h"

// Inicializa o ponteiro da instância
Camera *Camera::instance = nullptr;

// **********************************************************************
//  Camera::Camera(Player *player, Ponto *OBS, Ponto *ALVO, Ponto *VetorAlvo, KeyboardController keyboard)
//  Construtor da classe Camera
//
//  Parâmetros:
//      Player *player: Ponteiro para a instância do jogador.
//      Ponto *OBS: Ponteiro para o ponto de observação da câmera.
//      Ponto *ALVO: Ponteiro para o ponto alvo da câmera.
//      Ponto *VetorAlvo: Ponteiro para o vetor direção da câmera.
//      KeyboardController keyboard: Controlador de teclado para entrada do usuário.
// **********************************************************************
Camera::Camera(Player *player, Ponto *OBS, Ponto *ALVO, Ponto *VetorAlvo, KeyboardController keyboard)
    : player(player), OBS(OBS), ALVO(ALVO), VetorAlvo(VetorAlvo), keyboard(keyboard)
{
  instance = this; // Atribui a instância atual
}

// **********************************************************************
//  void Camera::setOBS(Ponto *OBS)
//  Define o ponto de observação da câmera.
//
//  Parâmetros:
//      Ponto *OBS: Ponteiro para o novo ponto de observação.
// **********************************************************************
void Camera::setOBS(Ponto *OBS)
{
  this->OBS = OBS;
}

// **********************************************************************
//  void Camera::setALVO(Ponto *ALVO)
//  Define o ponto alvo da câmera.
//
//  Parâmetros:
//      Ponto *ALVO: Ponteiro para o novo ponto alvo.
// **********************************************************************
void Camera::setALVO(Ponto *ALVO)
{
  this->ALVO = ALVO;
}

// **********************************************************************
//  void Camera::setVetorAlvo(Ponto *VetorAlvo)
//  Define o vetor direção da câmera.
//
//  Parâmetros:
//      Ponto *VetorAlvo: Ponteiro para o novo vetor direção.
// **********************************************************************
void Camera::setVetorAlvo(Ponto *VetorAlvo)
{
  this->VetorAlvo = VetorAlvo;
}

// **********************************************************************
//  void Camera::setAspectRatio(GLfloat AspectRatio)
//  Define a razão de aspecto da projeção da câmera.
//
//  Parâmetros:
//      GLfloat AspectRatio: A razão de aspecto da janela de visualização.
// **********************************************************************
void Camera::setAspectRatio(GLfloat AspectRatio)
{
  this->AspectRatio = AspectRatio;
}

// **********************************************************************
//  void Camera::lookSideways(int direction)
//  Faz a câmera olhar para os lados baseado na direção fornecida.
//
//  Parâmetros:
//      int direction: Direção do movimento (0 para esquerda, 1 para direita).
// **********************************************************************
void Camera::lookSideways(int direction)
{
  ALVO->x -= OBS->x;
  ALVO->z -= OBS->z;

  float alfa = (direction == 0) ? 0.05 : -0.05; // Define o ângulo de rotação
  float x = ALVO->x * cos(alfa) + ALVO->z * sin(alfa);
  float z = -ALVO->x * sin(alfa) + ALVO->z * cos(alfa);
  ALVO->x = x + OBS->x;
  ALVO->z = z + OBS->z;

  VetorAlvo->x = ALVO->x - OBS->x;
  VetorAlvo->y = ALVO->y - OBS->y;
  VetorAlvo->z = ALVO->z - OBS->z;

  player->setOBS(*OBS);
  player->setVetorAlvo(*VetorAlvo);
}

// **********************************************************************
//  void Camera::goForward(int direction)
//  Move a câmera para frente ou para trás baseado na direção fornecida.
//
//  Parâmetros:
//      int direction: Direção do movimento (0 para frente, 1 para trás).
// **********************************************************************
void Camera::goForward(int direction)
{
  float walkSpeed = direction == 0 ? 0.15 : -0.15;
  Ponto VetorAlvoUnitario = *VetorAlvo;
  VetorAlvoUnitario.versor(); // Normaliza o vetor direção

  VetorAlvoUnitario.multiplica(walkSpeed, walkSpeed, walkSpeed);
  OBS->soma(VetorAlvoUnitario.x, 0, VetorAlvoUnitario.z);
  ALVO->soma(VetorAlvoUnitario.x, 0, VetorAlvoUnitario.z);

  player->setOBS(*OBS);
  player->setVetorAlvo(*VetorAlvo);
}

// **********************************************************************
//  void Camera::updateCamera()
//  Atualiza a posição da câmera com base nas entradas do teclado.
// **********************************************************************
void Camera::updateCamera()
{
  if (keyboard.isKeyPressed('w'))
  {
    goForward(0); // Move para frente
  }
  if (keyboard.isKeyPressed('s'))
  {
    printf("s");
    goForward(1); // Move para trás
  }
  if (keyboard.isKeyPressed('a'))
  {
    lookSideways(0); // Olha para a esquerda
  }
  if (keyboard.isKeyPressed('d'))
  {
    lookSideways(1); // Olha para a direita
  }
  if (keyboard.isKeyPressed('q'))
  {
    player->raiseCannon(1); // Levanta o canhão
  }
  if (keyboard.isKeyPressed('e'))
  {
    player->lowerCannon(1); // Abaixa o canhão
  }

  // Adiciona a lógica de disparo apenas quando a tecla "espaço" for pressionada
  if (keyboard.isKeyPressed(' ') && !spaceKeyPressed)
  {
    Ponto cameraAlvo = *ALVO;
    player->dispararTiro(cameraAlvo); // Dispara um tiro
    printf(" disparou\n");
    spaceKeyPressed = true; // Marca que a tecla "espaço" foi pressionada
  }
  else if (!keyboard.isKeyPressed(' ') && spaceKeyPressed)
  {
    spaceKeyPressed = false; // Reseta quando a tecla "espaço" é liberada
  }

  player->updatePlayerPosition(); // Atualiza a posição do jogador
  glutPostRedisplay();            // Redesenha a cena
}

// **********************************************************************
//  void Camera::MygluPerspective(float fieldOfView, float aspect, float zNear, float zFar)
//  Define a perspectiva da câmera usando frustum.
//
//  Parâmetros:
//      float fieldOfView: Campo de visão vertical em graus.
//      float aspect: Razão de aspecto da janela.
//      float zNear: Distância do plano próximo.
//      float zFar: Distância do plano distante.
// **********************************************************************
void Camera::MygluPerspective(float fieldOfView, float aspect, float zNear, float zFar)
{
  GLfloat fH = tan(float(fieldOfView / 360.0f * 3.14159f)) * zNear;
  GLfloat fW = fH * aspect;
  glFrustum(-fW, fW, -fH, fH, zNear, zFar); // Define o frustum
}

// **********************************************************************
//  void Camera::PosicUser()
//  Posiciona a câmera e define os parâmetros da projeção perspectiva.
// **********************************************************************
void Camera::PosicUser()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  MygluPerspective(90, AspectRatio, 0.1, 50); // Projeção perspectiva

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(OBS->x, OBS->y, OBS->z,    // Posição do Observador
            ALVO->x, ALVO->y, ALVO->z, // Posição do Alvo
            0.0, 1.0, 0.0);            // Vetor up

  glGetFloatv(GL_MODELVIEW_MATRIX, &CameraMatrix[0][0]);
  InverteMatriz(CameraMatrix, InvCameraMatrix);
  SalvaMatrizDaCamera(InvCameraMatrix);
}

// **********************************************************************
//  void Camera::DefineLuz()
//  Define a iluminação da cena com propriedades específicas.
// **********************************************************************
void Camera::DefineLuz(void)
{
  GLfloat LuzAmbiente[] = {0.8, 0.8, 0.8};
  GLfloat LuzDifusa[] = {0.7, 0.7, 0.7};
  GLfloat PosicaoLuz0[] = {0.0f, 5.0f, 0.0f}; // Posição da Luz
  // GLfloat LuzEspecular[] = {1.0f, 1.0f, 1.0f};
  // GLfloat Especularidade[] = {1.0f, 1.0f, 1.0f};

  glEnable(GL_COLOR_MATERIAL); // Habilita o uso de cores

  glEnable(GL_LIGHTING); // Habilita a iluminação
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LuzAmbiente);
  glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa);
  // glLightfv(GL_LIGHT0, GL_SPECULAR, LuzEspecular);
  glLightfv(GL_LIGHT0, GL_POSITION, PosicaoLuz0);
  glEnable(GL_LIGHT0);

  // glMaterialfv(GL_FRONT, GL_SPECULAR, Especularidade); // Define a refletividade
  glMateriali(GL_FRONT, GL_SHININESS, 128); // Define a concentração do brilho
}

// **********************************************************************
//  void Camera::updateCameraStatic()
//  Atualiza a câmera estática se a instância existir.
// **********************************************************************
void Camera::updateCameraStatic()
{
  if (instance)
  {
    instance->updateCamera();
  }
}
