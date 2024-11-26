#ifndef CAMERA_H
#define CAMERA_H

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
#include "Player.h"
#include "Tools.h"
#include "Instancia.h"
#include "KeyboardController.h"
#include "PontosManager.h"

class Camera
{
public:
  /**
   * @brief Construtor da classe Camera.
   *
   * @param player Ponteiro para o objeto Player associado à câmera.
   * @param OBS Ponteiro para o ponto de observação.
   * @param ALVO Ponteiro para o alvo da câmera.
   * @param VetorAlvo Ponteiro para o vetor que define a direção do alvo.
   * @param keyboard Controlador do teclado.
   */
  Camera(Player *player, Ponto *OBS, Ponto *ALVO, Ponto *VetorAlvo, KeyboardController keyboard);

  /**
   * @brief Define um novo ponto de observação (OBS).
   *
   * @param OBS Ponteiro para o novo ponto de observação.
   */
  void setOBS(Ponto *OBS);

  /**
   * @brief Define um novo alvo (ALVO).
   *
   * @param ALVO Ponteiro para o novo alvo.
   */
  void setALVO(Ponto *ALVO);

  /**
   * @brief Define um novo vetor alvo (VetorAlvo).
   *
   * @param VetorAlvo Ponteiro para o novo vetor alvo.
   */
  void setVetorAlvo(Ponto *VetorAlvo);

  /**
   * @brief Define a razão de aspecto da câmera.
   *
   * @param AspectRatio Valor da razão de aspecto.
   */
  void setAspectRatio(GLfloat AspectRatio);

  /**
   * @brief Rotaciona a câmera lateralmente.
   *
   * @param direction Direção da rotação: 0 para direita, 1 para esquerda.
   */
  void lookSideways(int direction);

  /**
   * @brief Move a câmera para frente ou para trás.
   *
   * @param direction Direção do movimento: 0 para frente, 1 para trás.
   */
  void goForward(int direction);

  /**
   * @brief Atualiza a posição da câmera com base nas entradas do teclado.
   */
  void updateCamera();

  /**
   * @brief Método estático para ser usado com glutIdleFunc para atualizar a câmera.
   */
  static void updateCameraStatic();

  /**
   * @brief Define a iluminação da cena.
   */
  static void DefineLuz(void);

  /**
   * @brief Configura a perspectiva da câmera.
   *
   * @param fieldOfView Campo de visão em graus.
   * @param aspect Razão de aspecto da tela.
   * @param zNear Distância do plano de recorte próximo.
   * @param zFar Distância do plano de recorte distante.
   */
  void MygluPerspective(float fieldOfView, float aspect, float zNear, float zFar);

  /**
   * @brief Posiciona a câmera na cena.
   */
  void PosicUser();

  /**
   * @brief Retorna o ponto de observação (OBS).
   *
   * @return Ponteiro para o ponto de observação.
   */
  Ponto *getOBS() const { return OBS; }

  /**
   * @brief Retorna o alvo (ALVO).
   *
   * @return Ponteiro para o alvo.
   */
  Ponto *getALVO() const { return ALVO; }

  /**
   * @brief Retorna o vetor alvo (VetorAlvo).
   *
   * @return Ponteiro para o vetor alvo.
   */
  Ponto *getVetorAlvo() const { return VetorAlvo; }

  static Camera *instance; // Ponteiro estático para a instância

private:
  Ponto *OBS;                    // Ponteiro para o ponto de observação
  Ponto *ALVO;                   // Ponteiro para o alvo
  Ponto *VetorAlvo;              // Ponteiro para o vetor alvo
  Player *player;                // Ponteiro para o objeto Player
  GLfloat CameraMatrix[4][4];    // Matriz da câmera
  GLfloat InvCameraMatrix[4][4]; // Matriz inversa da câmera
  KeyboardController keyboard;   // Controlador do teclado
  bool spaceKeyPressed = false;

  // Variável para a razão de aspecto
  GLfloat AspectRatio;
};

#endif // CAMERA_H
