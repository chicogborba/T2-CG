#include <iostream>
#include <cmath>
#include <ctime>

// Incluir bibliotecas específicas do sistema operacional
#ifdef WIN32
#include <windows.h>
#include <glut.h>
#elif defined(__APPLE__)
#include <GLUT/glut.h>
#else // Assume Linux by default
#include <GL/glut.h>
#endif

// Incluir cabeçalhos personalizados
#include "ListaDeCoresRGB.h"
#include "Ponto.h"
#include "Instancia.h"
#include "Tools.h"
#include "Player.h"
#include "KeyboardController.h"
#include "Piso.h"
#include "Camera.h"
#include "Paredao.h"
#include "Tiro.h"
#include "TextureClass.h"
#include "Modelo3D.h"
#include "ListOfObjects.h"

#include <vector>

// Variáveis globais
Ponto OBS(0, 3, 10);          // Ponto de observação da câmera
Ponto ALVO(0, 0, 0);          // Ponto alvo da câmera
Ponto VetorAlvo = ALVO - OBS; // Vetor direção da câmera

// Instâncias de classes
KeyboardController keyboardController;
Player player(OBS, VetorAlvo);
Camera camera(&player, &OBS, &ALVO, &VetorAlvo, keyboardController);
Piso piso(25, 50, 100, 1);
Paredao paredao(25, 15, Ponto(-12.5, 0, 0), 100);
Modelo3D *arvore = nullptr;

// std::vector<Tiro> tiros;

// **********************************************************************
//  void init(void)
//  Inicializa os parâmetros globais de OpenGL
// **********************************************************************
void init(void)
{

    arvore = new Modelo3D(10.0f, -1.0f, 10.0f);                                                    // Posição inicial
    arvore->carregarModelo("/Users/franciscoborba/Downloads/CodeBlocks 2/assets/models/tree.obj"); // Carrega o modelo
    // 7, 84, 3
    arvore->setColor(0.17f, 0.23f, 0.02f); // Define a cor do modelo
    arvore->setEscala(8.0f, 8.0f, 8.0f);   // Dobra o tamanho
    arvore->setRotacao(0.0f, 45.0f, 0.0f); // Rotaciona 45 graus no eixo Y

    // Define a cor de fundo como um azul claro tipo o céu
    glClearColor(0.7f, 0.9f, 1.0f, 1.0f);

    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    piso.carregarTextura("/Users/franciscoborba/Downloads/CodeBlocks 2/assets/textures/grass.png");
    paredao.carregarTextura("/Users/franciscoborba/Downloads/CodeBlocks 2/assets/textures/brick.png");

    player.updatePlayerPosition();

    // Cria um tiro inicial para testes
    // Tiro tiro(player.getPosition(), Ponto(0, 0, 0), 0.1f);
    // tiros.push_back(tiro);
}

// **********************************************************************
//  void reshape(int w, int h)
//  Trata o redimensionamento da janela OpenGL
//
//  Parâmetros:
//      int w: A largura da janela em pixels.
//      int h: A altura da janela em pixels.
// **********************************************************************
void reshape(int w, int h)
{
    if (h == 0)
        h = 1; // Evita divisão por zero

    // Atualiza a proporção da tela
    camera.setAspectRatio(static_cast<float>(w) / h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h); // Ajusta a viewport para ocupar toda a janela
    camera.PosicUser();     // Posiciona a câmera
}

// **********************************************************************
//  void display(void)
//  Renderiza a cena 3D
// **********************************************************************
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Camera::DefineLuz(); // Define a iluminação da cena
    camera.PosicUser();  // Posiciona a câmera

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0, -1, 0);
    piso.desenhaChao(); // Desenha o chão
    paredao.desenhaParedao();
    glPopMatrix();

    player.drawPlayer(); // Desenha o jogador

    // std::cout << "Player position: " << player.getPosition().x << " " << player.getPosition().y << " " << player.getPosition().z << std::endl;

    // for (auto &tiro : tiros)
    // {
    //     tiro.updateTiro();
    //     tiro.drawTiro();
    // }

    // paredao.detectarColisao(player.getPosition());
    // usar o player.getTiros() para detectar colisão com os tiros

    // Loop sobre os tiros

    for (auto &tiro : player.getTiros())
    {
        // printar tiro.getPosition()
        // std::cout << "Tiro position: " << tiro.getPosition().x << " " << tiro.getPosition().y << " " << tiro.getPosition().z << std::endl;
        paredao.detectarColisao(tiro.getPosition());
    }

    player.updateTiros(); // Atualiza os tiros

    if (arvore)
    {
        arvore->desenhar();
    }

    glutSwapBuffers(); // Troca os buffers
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Computacao Grafica - Exemplo Basico 3D");

    init(); // Inicializa OpenGL

    // Registro das funções de callback
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(KeyboardController::keyDown);
    glutKeyboardUpFunc(KeyboardController::keyUp);
    glutIdleFunc(Camera::updateCameraStatic); // Atualiza a câmera

    glutMainLoop(); // Inicia o loop principal do GLUT
    return 0;
}
