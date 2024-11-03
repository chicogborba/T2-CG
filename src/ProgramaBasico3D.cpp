

#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

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

#include "ListaDeCoresRGB.h"
#include "Ponto.h"
#include "Instancia.h"
#include "Tools.h"
#include "Player.h"
#include "KeyboardController.h"
#include "Piso.h"

GLfloat AspectRatio = 0;

KeyboardController keyboardController;

Ponto OBS;
Ponto ALVO;
Ponto VetorAlvo;
GLfloat CameraMatrix[4][4];
GLfloat InvCameraMatrix[4][4];

Ponto PosicaoDoObjeto(0, 0, 4);
Player player(OBS, VetorAlvo);
Piso piso(5, 5, 100, 1);

float walkSpeed = 0.15;

// nao foi pro h
void goForward(int direction)
{
    Ponto VetorAlvoUnitario = VetorAlvo;
    VetorAlvoUnitario.versor();
    if (direction == 0)
    {
        VetorAlvoUnitario.multiplica(walkSpeed, walkSpeed, walkSpeed);
    }
    else if (direction == 1)
    {
        VetorAlvoUnitario.multiplica(-walkSpeed, -walkSpeed, -walkSpeed);
    }
    OBS.soma(VetorAlvoUnitario.x, 0, VetorAlvoUnitario.z);
    ALVO.soma(VetorAlvoUnitario.x, 0, VetorAlvoUnitario.z);

    player.setOBS(OBS);
    player.setVetorAlvo(VetorAlvo);
}

void lookSideways(int direction)
{
    ALVO.x -= OBS.x;
    ALVO.z -= OBS.z;

    float alfa = (direction == 0) ? 0.05 : -0.05;
    float x = ALVO.x * cos(alfa) + ALVO.z * sin(alfa);
    float z = -ALVO.x * sin(alfa) + ALVO.z * cos(alfa);
    ALVO.x = x;
    ALVO.z = z;

    ALVO.x += OBS.x;
    ALVO.z += OBS.z;

    VetorAlvo.x = ALVO.x - OBS.x;
    VetorAlvo.y = ALVO.y - OBS.y;
    VetorAlvo.z = ALVO.z - OBS.z;

    player.setOBS(OBS);
    player.setVetorAlvo(VetorAlvo);
}

// nao foi pro h
void updateCamera()
{
    if (keyboardController.isKeyPressed('w'))
    {
        goForward(0);
    }
    if (keyboardController.isKeyPressed('s'))
    {
        goForward(1);
    }
    if (keyboardController.isKeyPressed('a'))
    {
        lookSideways(0);
    }
    if (keyboardController.isKeyPressed('d'))
    {
        lookSideways(1);
    }
    player.updatePlayerPosition();
    glutPostRedisplay();
}

// **********************************************************************
//  void init(void)
//        Inicializa os parametros globais de OpenGL
// **********************************************************************
void init(void)
{
    glClearColor(0.4f, 1.0f, 0.0f, 1.0f); // Fundo de tela preto

    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    // glShadeModel(GL_FLAT);

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    ALVO = Ponto(0, 0, 0);
    OBS = Ponto(0, 3, 10);
    VetorAlvo = ALVO - OBS;
    player.updatePlayerPosition();
}

// void DesenhaParedao()
// {
//     glPushMatrix();
//     glRotatef(90, 0, 0, 1);
//     DesenhaPiso();
//     glPopMatrix();
// }

// **********************************************************************
//  void DefineLuz(void)
// **********************************************************************
void DefineLuz(void)
{
    // Define cores para um objeto dourado
    // GLfloat LuzAmbiente[]   = {0.0, 0.0, 0.0 } ;
    GLfloat LuzAmbiente[] = {0.4, 0.4, 0.4};
    GLfloat LuzDifusa[] = {0.7, 0.7, 0.7};
    // GLfloat LuzDifusa[]   = {0, 0, 0};
    GLfloat PosicaoLuz0[] = {0.0f, 3.0f, 5.0f}; // Posi��o da Luz
    GLfloat LuzEspecular[] = {0.9f, 0.9f, 0.9};
    // GLfloat LuzEspecular[] = {0.0f, 0.0f, 0.0 };

    GLfloat Especularidade[] = {1.0f, 1.0f, 1.0f};

    // ****************  Fonte de Luz 0

    glEnable(GL_COLOR_MATERIAL);

    // Habilita o uso de ilumina��o
    glEnable(GL_LIGHTING);

    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LuzAmbiente);
    // Define os parametros da luz n�mero Zero
    glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, LuzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, PosicaoLuz0);
    glEnable(GL_LIGHT0);

    // Ativa o "Color Tracking"
    glEnable(GL_COLOR_MATERIAL);

    // Define a reflectancia do material
    glMaterialfv(GL_FRONT, GL_SPECULAR, Especularidade);

    // Define a concentra��oo do brilho.
    // Quanto maior o valor do Segundo parametro, mais
    // concentrado ser� o brilho. (Valores v�lidos: de 0 a 128)
    glMateriali(GL_FRONT, GL_SHININESS, 128);
}
// **********************************************************************

void MygluPerspective(float fieldOfView, float aspect, float zNear, float zFar)
{
    // https://stackoverflow.com/questions/2417697/gluperspective-was-removed-in-opengl-3-1-any-replacements/2417756#2417756
    //  The following code is a fancy bit of math that is equivilant to calling:
    //  gluPerspective( fieldOfView/2.0f, width/height , 0.1f, 255.0f )
    //  We do it this way simply to avoid requiring glu.h
    // GLfloat zNear = 0.1f;
    // GLfloat zFar = 255.0f;
    // GLfloat aspect = float(width)/float(height);
    GLfloat fH = tan(float(fieldOfView / 360.0f * 3.14159f)) * zNear;
    GLfloat fW = fH * aspect;
    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}
// **********************************************************************
//  void PosicUser()
// **********************************************************************
void PosicUser()
{

    // Define os par�metros da proje��o Perspectiva
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    MygluPerspective(90, AspectRatio, 0.1, 50); // Projecao perspectiva

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // OBS = Ponto(0, 0, 10);
    // ALVO = Ponto(0, 0, 0);

    gluLookAt(OBS.x, OBS.y, OBS.z,    // Posi��o do Observador
              ALVO.x, ALVO.y, ALVO.z, // Posi��o do Alvo
              0.0, 1.0, 0.0);

    glGetFloatv(GL_MODELVIEW_MATRIX, &CameraMatrix[0][0]);
    InverteMatriz(CameraMatrix, InvCameraMatrix);
    SalvaMatrizDaCamera(InvCameraMatrix);

    // ImprimeMatriz(CameraMatrix);
    // cout << "Inversa:\n";
    // ImprimeMatriz(InvCameraMatrix);
}
// **********************************************************************
//  void reshape( int w, int h )
//		trata o redimensionamento da janela OpenGL
//
// **********************************************************************
void reshape(int w, int h)
{

    // Evita divis�o por zero, no caso de uam janela com largura 0.
    if (h == 0)
        h = 1;
    // Ajusta a rela��o entre largura e altura para evitar distor��o na imagem.
    // Veja fun��o "PosicUser".
    AspectRatio = 1.0f * w / h;
    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Seta a viewport para ocupar toda a janela
    glViewport(0, 0, w, h);
    // cout << "Largura" << w << endl;

    PosicUser();
}

// **********************************************************************
//  void display( void )
// **********************************************************************
void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    DefineLuz();

    PosicUser();

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslatef(0, -1, 0);
    piso.desenhaChao();
    glPopMatrix();

    player.drawPlayer();

    glutSwapBuffers();
}

// **********************************************************************
//  void main ( int argc, char** argv )
// **********************************************************************
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Computacao Grafica - Exemplo Basico 3D");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(KeyboardController::keyDown);
    glutKeyboardUpFunc(KeyboardController::keyUp);
    glutIdleFunc(updateCamera);

    glutMainLoop();
    return 0;
}
