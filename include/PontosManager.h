#ifndef PONTOS_MANAGER_H
#define PONTOS_MANAGER_H

#include <iostream>

// Classe responsável pela gestão dos pontos
class PontosManager
{
public:
  // Variável estática que armazena os pontos
  static int pontos;

  // Getter para obter os pontos
  static int getPontos()
  {
    return pontos;
  }

  // Setter para modificar os pontos
  static void adicionarPontos(int pontosGanho)
  {
    if (pontosGanho < 0)
    {
      std::cout << "Não é permitido adicionar pontos negativos!" << std::endl;
    }
    else
    {
      pontos += pontosGanho;
    }
  }

  // Método para definir os pontos diretamente
  static void setPontos(int novoPontos)
  {
    if (novoPontos >= 0)
    {
      pontos = novoPontos;
    }
    else
    {
      std::cout << "Pontos não podem ser negativos!" << std::endl;
    }
  }
};

#endif // PONTOS_MANAGER_H
