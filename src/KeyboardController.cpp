#include "KeyboardController.h"

// Inicializa o array estático fora da classe
bool KeyboardController::keyStates[256] = {false};

KeyboardController::KeyboardController()
{
  // Opcional: Reinicializa os estados das teclas ao criar uma instância
  for (int i = 0; i < 256; i++)
  {
    keyStates[i] = false;
  }
}

// Definições dos métodos estáticos
void KeyboardController::keyDown(unsigned char key, int x, int y)
{
  keyStates[key] = true; // Marca a tecla como pressionada
}

void KeyboardController::keyUp(unsigned char key, int x, int y)
{
  keyStates[key] = false; // Marca a tecla como liberada
}

bool KeyboardController::isKeyPressed(unsigned char key) const
{
  return keyStates[key]; // Retorna o estado da tecla
}
