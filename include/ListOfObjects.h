#ifndef LISTOFOBJECTS_H
#define LISTOFOBJECTS_H

#include "Modelo3D.h"
#include <vector>
#include <string>
#include <iostream>

// Estrutura para armazenar as propriedades de um modelo
struct ObjectProperties
{
  std::string filePath; // Caminho para o arquivo do modelo
  Ponto position;       // Posição do modelo
  Ponto scale;          // Escala do modelo
  Ponto rotation;       // Rotação do modelo
  float color[3];       // Cor do modelo (RGB)
};

class ListOfObjects
{
private:
  std::vector<Modelo3D *> objects;        // Lista de modelos carregados
  std::vector<ObjectProperties> settings; // Configurações de cada modelo

public:
  ListOfObjects();
  ~ListOfObjects();

  void addObject(const std::string &filePath, const Ponto &position, const Ponto &scale, const Ponto &rotation, float r, float g, float b);
  void initializeObjects();
  void renderAll();
};

#endif // LISTOFOBJECTS_H
