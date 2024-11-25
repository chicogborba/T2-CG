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
#include "PontosManager.h"

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

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
Modelo3D *arvore2 = nullptr;
Modelo3D *arvore3 = nullptr;
Modelo3D *arvore4 = nullptr;
Modelo3D *arvore5 = nullptr;
Modelo3D *arvore6 = nullptr;

Modelo3D *fence = nullptr;
Modelo3D *fence2 = nullptr;

Modelo3D *fence3 = nullptr;
Modelo3D *fence4 = nullptr;

Modelo3D *fence5 = nullptr;
Modelo3D *fence6 = nullptr;

Modelo3D *fence7 = nullptr;
Modelo3D *fence8 = nullptr;

// Uma lista de Modelos3D pra renderizar todos de uma vez
std::vector<Modelo3D> modelos;

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
    modelos.push_back(*arvore);

    arvore2 = new Modelo3D(10.0f, -1.0f, -10.0f);                                                   // Posição inicial
    arvore2->carregarModelo("/Users/franciscoborba/Downloads/CodeBlocks 2/assets/models/tree.obj"); // Carrega o modelo
    arvore2->setColor(0.17f, 0.23f, 0.02f);                                                         // Define a cor do modelo
    arvore2->setEscala(8.0f, 8.0f, 8.0f);                                                           // Dobra o tamanho
    arvore2->setRotacao(0.0f, 45.0f, 0.0f);                                                         // Rotaciona 45 graus no eixo Y
    modelos.push_back(*arvore2);

    arvore3 = new Modelo3D(-10.0f, -1.0f, 15.0f);                                                   // Posição inicial
    arvore3->carregarModelo("/Users/franciscoborba/Downloads/CodeBlocks 2/assets/models/tree.obj"); // Carrega o modelo
    arvore3->setColor(0.17f, 0.23f, 0.02f);                                                         // Define a cor do modelo
    arvore3->setEscala(8.0f, 8.0f, 8.0f);                                                           // Dobra o tamanho
    arvore3->setRotacao(0.0f, 45.0f, 0.0f);                                                         // Rotaciona 45 graus no eixo Y
    modelos.push_back(*arvore3);

    arvore4 = new Modelo3D(-10.0f, -1.0f, -15.0f);                                                  // Posição inicial
    arvore4->carregarModelo("/Users/franciscoborba/Downloads/CodeBlocks 2/assets/models/tree.obj"); // Carrega o modelo
    arvore4->setColor(0.17f, 0.23f, 0.02f);                                                         // Define a cor do modelo
    arvore4->setEscala(8.0f, 8.0f, 8.0f);                                                           // Dobra o tamanho
    arvore4->setRotacao(0.0f, 45.0f, 0.0f);                                                         // Rotaciona 45 graus no eixo Y
    modelos.push_back(*arvore4);

    arvore5 = new Modelo3D(10.0f, -1.0f, 18.0f);                                                    // Posição inicial
    arvore5->carregarModelo("/Users/franciscoborba/Downloads/CodeBlocks 2/assets/models/tree.obj"); // Carrega o modelo
    arvore5->setColor(0.17f, 0.23f, 0.02f);                                                         // Define a cor do modelo
    arvore5->setEscala(8.0f, 8.0f, 8.0f);                                                           // Dobra o tamanho
    arvore5->setRotacao(0.0f, 45.0f, 0.0f);                                                         // Rotaciona 45 graus no eixo Y
    modelos.push_back(*arvore5);

    arvore6 = new Modelo3D(-8.0f, -1.0f, -8.0f);                                                    // Posição inicial
    arvore6->carregarModelo("/Users/franciscoborba/Downloads/CodeBlocks 2/assets/models/tree.obj"); // Carrega o modelo
    arvore6->setColor(0.17f, 0.23f, 0.02f);                                                         // Define a cor do modelo
    arvore6->setEscala(8.0f, 8.0f, 8.0f);                                                           // Dobra o tamanho
    arvore6->setRotacao(0.0f, 45.0f, 0.0f);                                                         // Rotaciona 45 graus no eixo Y
    modelos.push_back(*arvore6);

    fence = new Modelo3D(-12.5f, 1.5f, 7.0f);                                                      // Posição inicial
    fence->carregarModelo("/Users/franciscoborba/Downloads/CodeBlocks 2/assets/models/fence.obj"); // Carrega o modelo
    fence->setColor(0.54f, 0.27f, 0.07f);                                                          // Define a cor do modelo
    fence->setEscala(0.6f, 0.25f, 0.25f);                                                          // Dobra o tamanho
    fence->setRotacao(0.0f, 90.0f, 0.0f);                                                          // Rotaciona 45 graus no eixo Y
    modelos.push_back(*fence);

    fence2 = new Modelo3D(-12.5f, 1.5f, 18.0f);                                                     // Posição inicial
    fence2->carregarModelo("/Users/franciscoborba/Downloads/CodeBlocks 2/assets/models/fence.obj"); // Carrega o modelo
    fence2->setColor(0.54f, 0.27f, 0.07f);                                                          // Define a cor do modelo
    fence2->setEscala(0.6f, 0.25f, 0.25f);                                                          // Dobra o tamanho
    fence2->setRotacao(0.0f, 90.0f, 0.0f);                                                          // Rotaciona 45 graus no eixo Y
    modelos.push_back(*fence2);

    fence3 = new Modelo3D(12.0f, 1.5f, 7.0f);                                                       // Posição inicial
    fence3->carregarModelo("/Users/franciscoborba/Downloads/CodeBlocks 2/assets/models/fence.obj"); // Carrega o modelo
    fence3->setColor(0.54f, 0.27f, 0.07f);                                                          // Define a cor do modelo
    fence3->setEscala(0.6f, 0.25f, 0.25f);                                                          // Dobra o tamanho
    fence3->setRotacao(0.0f, 90.0f, 0.0f);                                                          // Rotaciona 45 graus no eixo Y
    modelos.push_back(*fence3);

    fence4 = new Modelo3D(12.0f, 1.5f, 18.0f);                                                      // Posição inicial
    fence4->carregarModelo("/Users/franciscoborba/Downloads/CodeBlocks 2/assets/models/fence.obj"); // Carrega o modelo
    fence4->setColor(0.54f, 0.27f, 0.07f);                                                          // Define a cor do modelo
    fence4->setEscala(0.6f, 0.25f, 0.25f);                                                          // Dobra o tamanho
    fence4->setRotacao(0.0f, 90.0f, 0.0f);                                                          // Rotaciona 45 graus no eixo Y
    modelos.push_back(*fence4);

    fence5 = new Modelo3D(-12.5f, 1.5f, -7.0f);                                                     // Posição inicial
    fence5->carregarModelo("/Users/franciscoborba/Downloads/CodeBlocks 2/assets/models/fence.obj"); // Carrega o modelo
    fence5->setColor(0.54f, 0.27f, 0.07f);                                                          // Define a cor do modelo
    fence5->setEscala(0.6f, 0.25f, 0.25f);                                                          // Dobra o tamanho
    fence5->setRotacao(0.0f, 90.0f, 0.0f);                                                          // Rotaciona 45 graus no eixo Y
    modelos.push_back(*fence5);

    fence6 = new Modelo3D(-12.5f, 1.5f, -18.0f);                                                    // Posição inicial
    fence6->carregarModelo("/Users/franciscoborba/Downloads/CodeBlocks 2/assets/models/fence.obj"); // Carrega o modelo
    fence6->setColor(0.54f, 0.27f, 0.07f);                                                          // Define a cor do modelo
    fence6->setEscala(0.6f, 0.25f, 0.25f);                                                          // Dobra o tamanho
    fence6->setRotacao(0.0f, 90.0f, 0.0f);                                                          // Rotaciona 45 graus no eixo Y
    modelos.push_back(*fence6);

    fence7 = new Modelo3D(12.0f, 1.5f, -7.0f);                                                      // Posição inicial
    fence7->carregarModelo("/Users/franciscoborba/Downloads/CodeBlocks 2/assets/models/fence.obj"); // Carrega o modelo
    fence7->setColor(0.54f, 0.27f, 0.07f);                                                          // Define a cor do modelo
    fence7->setEscala(0.6f, 0.25f, 0.25f);                                                          // Dobra o tamanho
    fence7->setRotacao(0.0f, 90.0f, 0.0f);                                                          // Rotaciona 45 graus no eixo Y
    modelos.push_back(*fence7);

    fence8 = new Modelo3D(12.0f, 1.5f, -18.0f);                                                     // Posição inicial
    fence8->carregarModelo("/Users/franciscoborba/Downloads/CodeBlocks 2/assets/models/fence.obj"); // Carrega o modelo
    fence8->setColor(0.54f, 0.27f, 0.07f);                                                          // Define a cor do modelo
    fence8->setEscala(0.6f, 0.25f, 0.25f);                                                          // Dobra o tamanho
    fence8->setRotacao(0.0f, 90.0f, 0.0f);                                                          // Rotaciona 45 graus no eixo Y
    modelos.push_back(*fence8);

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
}

void renderBitmapString(float x, float y, void *font, const char *string)
{
    // Posiciona o texto em coordenadas de tela
    glRasterPos2f(x, y);
    while (*string)
    {
        glutBitmapCharacter(font, *string);
        ++string;
    }
}

void drawHUD()
{
    // Salva a matriz de projeção e muda para ortográfica
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    // Projeção ortográfica ajustada à janela
    gluOrtho2D(0, 800, 0, 600);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Desenha o texto no canto superior esquerdo
    glColor3f(1.0f, 1.0f, 1.0f); // Cor branca para o texto
    std::string pontosStr = "Pontos: " + std::to_string(PontosManager::getPontos());
    renderBitmapString(10, 580, GLUT_BITMAP_HELVETICA_18, pontosStr.c_str());

    // Restaura as matrizes de projeção e modelagem
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
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

    for (auto &tiro : player.getTiros())
    {
        paredao.detectarColisao(tiro.getPosition());
    }

    player.updateTiros(); // Atualiza os tiros

    for (auto &modelo : modelos)
    {
        modelo.desenhar();
    }

    drawHUD();         // Desenha o HUD
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
