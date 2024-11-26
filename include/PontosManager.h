#ifndef PONTOS_MANAGER_H
#define PONTOS_MANAGER_H

#include <iostream>

// Classe responsável pela gestão dos pontos
class PontosManager
{
public:
  // Variáveis estáticas que armazenam os pontos e a velocidade do tiro
  static int pontos;
  static int velocidadeTiro;

  // Getter para obter os pontos
  static int getPontos()
  {
    return pontos;
  }

  static int getVelocidadeTiro()
  {
    return velocidadeTiro;
  }

  // Adicionar pontos ao total
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

  // Adicionar velocidade ao tiro, respeitando o limite máximo
  static void adicionarVelocidadeTiro(int velocidadeGanho)
  {
    if (velocidadeGanho < 0)
    {
      std::cout << "Não é permitido adicionar velocidade negativa!" << std::endl;
    }
    else
    {
      velocidadeTiro += velocidadeGanho;
      if (velocidadeTiro > 100)
      {
        velocidadeTiro = 100;
        std::cout << "Velocidade do tiro atingiu o máximo permitido (100)!" << std::endl;
      }
    }
  }

  // Diminuir a velocidade do tiro, respeitando o limite mínimo
  static void diminuirVelocidadeTiro(int velocidadePerdida)
  {
    if (velocidadePerdida < 0)
    {
      std::cout << "Não é permitido diminuir velocidade negativa!" << std::endl;
    }
    else
    {
      velocidadeTiro -= velocidadePerdida;
      if (velocidadeTiro < 10)
      {
        velocidadeTiro = 10;
        std::cout << "Velocidade do tiro atingiu o mínimo permitido (10)!" << std::endl;
      }
    }
  }

  // Definir diretamente o valor dos pontos
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

  // Definir diretamente a velocidade do tiro, respeitando os limites
  static void setVelocidadeTiro(int novaVelocidade)
  {
    if (novaVelocidade >= 10 && novaVelocidade <= 100)
    {
      velocidadeTiro = novaVelocidade;
    }
    else if (novaVelocidade < 10)
    {
      velocidadeTiro = 10;
      std::cout << "Velocidade do tiro não pode ser menor que 10!" << std::endl;
    }
    else if (novaVelocidade > 100)
    {
      velocidadeTiro = 100;
      std::cout << "Velocidade do tiro não pode ser maior que 100!" << std::endl;
    }
  }
};

#endif // PONTOS_MANAGER_H
