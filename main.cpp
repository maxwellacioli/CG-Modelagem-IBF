#include "main.h"

// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f,z=5.0f;

float right_door_pivot[] = {-2.55f, 1.25f, -12.10f};
float left_door_pivot[] = {-4.0f, 1.25f, -13.55f};

GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};

float angle = 0.0f;

float right_door_angle = -45.0f;
float left_door_angle = -45.0f;

void drawGrass() {
    glPushMatrix();
    glColor3f(0.0f,1.f,0.0f);
    glTranslatef(0.0f, 0.0f, -3.0f);
    glScalef(10.0, 0.0, 5.0);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0f,1.f,0.0f);
    glTranslatef(0.0f, 0.0f, -7.0f);
    glScalef(10.0, 0.0, 5.0);
//    glutSolidCube(1.0f);
    glPopMatrix();
}

//t_x = translação em x
//s_x = escala em x
//r_x = rotação em x
void drawCube(float t_x, float t_y, float t_z, float s_x, float s_y, float s_z,
    float r_x, float r_y, float r_z, float cube_side, float r, float g, float b) {
    glPushMatrix();
    glColor3f(r, g, b);
    glTranslatef(t_x, t_y, t_z);
    glScalef(s_x, s_y, s_z);
    glutSolidCube(cube_side);
    glPopMatrix();
}

void drawTower() {
//Desenha a pilastra da cruz
  glPushMatrix();
  glColor3f(0.66f,0.66f,0.66f);
  glTranslatef(0.0f, 3.75f, -7.0f);
  glScalef(1.0, 15.0, 1.0);
//  glutSolidCube(0.5f);
  glPopMatrix();

    drawCube(0.0f, 3.75f, -7.0f, 1.0f, 15.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.66f, 0.66f, 0.66f);

//Desenha a base da cruz
  glPushMatrix();
  glTranslatef(0.0f, 0.25f, -7.0f);
  glScalef(1.0, 0.25, 1.0);
  glutSolidCube(2.0);
  glPopMatrix();

//Desenha a barra central da cruz
  glPushMatrix();
  glTranslatef(0.0f, 5.0f, -7.0f);
  glScalef(4.0, 0.25, 1.0);
  glutSolidCube(0.5);
  glPopMatrix();
}

void drawEntrance() {

//teta entrada
  glPushMatrix();
  glTranslatef(-0.5f, 2.25f, -7.0f);
  glScalef(11.0, 0.5, 4.0);
  glutSolidCube(1.0);
  glPopMatrix();

//coluna entrada
  glPushMatrix();
  glTranslatef(-4.25f, 1.0f, -7.0f);
  glScalef(0.5, 2.0, 1.0);
  glutSolidCube(1.0);
  glPopMatrix();
}

void drawTemple() {
//Desenha parede frontal da direita da entreda
    glPushMatrix();
    glTranslatef(2.0f, 1.25f, -9.25f);
    glScalef(12.0, 5.0, 1.0);
    glutSolidCube(0.5);
    glPopMatrix();

//Desenha parede frontal da esquerda da entreda
    glPushMatrix();
    glTranslatef(-4.25f, 1.25f, -9.25f);
    glScalef(7.0, 5.0, 1.0);
    glutSolidCube(0.5);
    glPopMatrix();

//Desenha parede direita do L da porta direita da entreda
    glPushMatrix();
    glTranslatef(-0.75f, 2.75f, -11.0f);
    glScalef(0.5, 5.5, 3.0);
    glutSolidCube(1.0);
    glPopMatrix();

//parede superior entrada (colocar textura)
    glPushMatrix();
    glTranslatef(-0.5f, 4.25f, -9.25f);
    glScalef(11.0, 3.5, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

//parede fundo entrada
    glPushMatrix();
    glTranslatef(-1.75f, 2.75f, -12.25f);
    glScalef(1.5, 5.5, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

//parede lateral esquerda do templo
    glPushMatrix();
    glColor3f(0.66f,0.66f,0.66f);
    glTranslatef(-5.75f, 2.75f, -17.0f);
    glScalef(0.5, 5.5, 15.0);
    glutSolidCube(1.0);
    glPopMatrix();

//parede lateral junta a porta esquerda do templo
    glPushMatrix();
    glTranslatef(-4.0f, 2.75f, -15.3f);
    glScalef(0.25, 5.5, 3.4);
    glutSolidCube(1.0);
    glPopMatrix();

//parede fundo(2), fica depois da porta
    glPushMatrix();
    glTranslatef(-4.69f, 2.75f, -17.25f);
    glScalef(1.63, 5.5, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

//parede lateral direita do templo
    glPushMatrix();
    glColor3f(0.66f,0.66f,0.66f);
    glTranslatef(4.75f, 2.75f, -17.0f);
    glScalef(0.5, 5.5, 15.0);
    glutSolidCube(1.0);
    glPopMatrix();

//parede do fundo do templo
    glPushMatrix();
    glColor3f(0.66f,0.66f,0.66f);
    glTranslatef(-0.5f, 2.75f, -24.75f);
    glScalef(11.0, 5.5, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

//teto do templo
    glPushMatrix();
    glColor3f(0.66f,0.66f,0.66f);
    glTranslatef(-0.5f, 5.75f, -17.25f);
    glScalef(11.0, 0.5, 15.5);
    glutSolidCube(1.0);
    glPopMatrix();

//teto interno entrada do templo (diagonal)
    glPushMatrix();
    glColor3f(0.66f,0.66f,0.66f);
    glTranslatef(-4.0225f, 4.0f, -12.093f);
    glRotatef(-45.0f, 0, 1, 0);
    glScalef(2.3, 3.0, 2.0);
    glutSolidCube(1.0);
    glPopMatrix();

//teto interno entrada do templo (parte horizontal olhando de frente para o templo)
    glPushMatrix();
    glColor3f(0.66f,0.66f,0.66f);
    glTranslatef(-3.25f, 3.0f, -10.75f);
    glScalef(4.5, 1.0, 2.5);
    glutSolidCube(1.0);
    glPopMatrix();

//teto interno entrada do templo (parte vertical olhando de frente para o templo)
    glPushMatrix();
    glColor3f(0.66f,0.66f,0.66f);
    glTranslatef(-4.81f, 3.0f, -13.25f);
    glScalef(1.375, 1.0, 7.5);
    glutSolidCube(1.0);
    glPopMatrix();

}


//TODO: fazer rotaçao da porta no eixo y para simular abertura e fechamento da mesma
void drawDoor() {
//    porta direita
    glPushMatrix();
    glColor3f(1.0f,1.0f,0.0f);
    glTranslatef(right_door_pivot[0], right_door_pivot[1], right_door_pivot[2]);
    glRotatef(right_door_angle, 0, 1, 0);
    glTranslatef(-0.5f, 0.0f, 0.0f);
    glScalef(1.0, 2.5, 0.1f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f,1.0f,0.0f);
    glTranslatef(left_door_pivot[0], left_door_pivot[1], left_door_pivot[2]);
    glRotatef(left_door_angle, 0, 1, 0);
    glTranslatef(+0.5f, 0.0f, 0.0f);
    glScalef(1.0, 2.5, 0.1f);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawFloor() {

  glPushMatrix();
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_QUADS);
  glVertex3f(-50.0f, 0.0f, -50.0f);
  glVertex3f(-50.0f, 0.0f, 50.0f);
  glVertex3f( 50.0f, 0.0f, 50.0f);
  glVertex3f( 50.0f, 0.0f, -50.0f);
  glEnd();
  glPopMatrix();
}

void display()
{
  // Clear Color and Depth Buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
  // Reset transformations
  glLoadIdentity();
  // Set the camera
  gluLookAt(  x, 1.0f, z,
  x+lx, 1.0f, z+lz,
  0.0f, 1.0f, 0.0f);

//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  drawGrass();
  drawFloor();
  drawTower();
  drawEntrance();
  drawTemple();
  drawDoor();

  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch(key){
        case 'o':
        right_door_angle+=1.0f;
        left_door_angle-=1.0f;
        glutPostRedisplay();
        break;

        case 'c':
        right_door_angle-=1.0f;
        left_door_angle+=1.0f;
        glutPostRedisplay();
        break;
    }
}

void processSpecialKeys(int key, int xx, int yy)
{

float fraction = 0.1f;

  switch (key)
  {
    case GLUT_KEY_LEFT :
    angle -= 0.01f;
    lx = sin(angle);
    lz = -cos(angle);
    break;
    case GLUT_KEY_RIGHT :
    angle += 0.01f;
    lx = sin(angle);
    lz = -cos(angle);
    break;
    case GLUT_KEY_UP :
    x += lx * fraction;
    z += lz * fraction;
    break;
    case GLUT_KEY_DOWN :
    x -= lx * fraction;
    z -= lz * fraction;
    break;
  }
}

void init() {
  glClearColor(0.0, 0.0, 1.0, 0.0);

  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  glEnable(GL_COLOR_MATERIAL);

  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);


}

void reshape(GLsizei width, GLsizei height)
{
  // Prevent a divide by zero, when window is too short
  // (you cant make a window of zero width).
  if (height == 0) {
      height = 1;
  }

  // Set the viewport to be the entire window
  glViewport(0, 0, width, height);

  float ratio = width * 1.0 / height;

  // Use the Projection Matrix
  glMatrixMode(GL_PROJECTION);

  // Reset Matrix
  glLoadIdentity();

  // Set the correct perspective.
  gluPerspective(45.0f, ratio, 0.1f, 100.0f);

  // Get Back to the Modelview
  glMatrixMode(GL_MODELVIEW);

}

int main(int argc,char **argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInitWindowPosition(10, 10);

  if(!glutCreateWindow("IGREJA BATISTA - FAROL")) {
    fprintf(stderr,"Error opening a window.\n");
    exit(-1);
  }

  init();

  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(display);
  glutSpecialFunc(processSpecialKeys);
  //glutPassiveMotionFunc(mouseMotion);
  //glutMouseFunc(mouse);

  //glutIdleFunc(animate);
  glutMainLoop();

  return 0;
}
