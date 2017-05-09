#include "main.h"

#include <fstream>
#include <SFML/Graphics.hpp>

// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=-5.0f,z=6.0f, y=1.0f;

float right_door_pivot[] = {-2.55f, 1.25f, -12.10f};
float left_door_pivot[] = {-4.0f, 1.25f, -13.55f};

GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_position[] = {0.0, 1.0, 1.0, 1.0};

float angle = 0.0f;

float right_door_angle = -45.0f;
float left_door_angle = -45.0f;

float glass_alpha = 0.5f;

GLuint texture_id[20];

void drawCube(GLdouble size, int *tex) {
  static GLfloat n[6][3] =
  {
    {-1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, -1.0}
  };
  static GLint faces[6][4] =
  {
    {0, 1, 2, 3},
    {3, 2, 6, 7},
    {7, 6, 5, 4},
    {4, 5, 1, 0},
    {5, 6, 2, 1},
    {7, 4, 0, 3}
  };
  GLfloat v[8][3];
  GLint i;

  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

  for (i = 5; i >= 0; i--) {
    if(tex[i] >= 0) {
      glBindTexture(GL_TEXTURE_2D, texture_id[tex[i]]);
    }
    glBegin(GL_QUADS);
    glNormal3fv(&n[i][0]);
    if(i==1)
      glTexCoord2f(1.0f, 0.0f);
    else
      glTexCoord2f(0.0f, 0.0f);
    glVertex3fv(&v[faces[i][0]][0]);
    if(i==1)
      glTexCoord2f(0.0f, 0.0f);
    else
      glTexCoord2f(1.0f, 0.0f);
    glVertex3fv(&v[faces[i][1]][0]);
    if(i==1)
      glTexCoord2f(0.0f, 1.0f);
    else
      glTexCoord2f(1.0f, 1.0f);
    glVertex3fv(&v[faces[i][2]][0]);
    if(i==1)
      glTexCoord2f(1.0f, 1.0f);
    else
      glTexCoord2f(0.0f, 1.0f);
    glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
    if(tex[i] >= 0) {
      glBindTexture(GL_TEXTURE_2D, 0);
    }
  }
}

void drawOfficeDesk(float x, float z) {
	glColor3f(1.0f, 1.0f, 1.0f);
	
	int office_desk_texture[] = {9, 9, 9, 9, 9, 9};
    
    //base esquerda
    glPushMatrix();
    glTranslatef(x, 0.125f, z);
    glScalef(0.2, 0.1, 0.7);
    drawCube(1.0f, office_desk_texture);
    glPopMatrix();

	//lateral esquerda
	glPushMatrix();
    glTranslatef(x, 0.4f, z);
    glScalef(0.1, 0.5f, 0.4);
    drawCube(1.0f, office_desk_texture);
    glPopMatrix();
     
    //base direita
    glPushMatrix();
    glTranslatef(x+1, 0.125f, z);
    glScalef(0.2, 0.1, 0.7);
    drawCube(1.0f, office_desk_texture);
    glPopMatrix();    
    
    //lateral direita
	glPushMatrix();
    glTranslatef(x+1, 0.4f, z);
    glScalef(0.1, 0.5f, 0.4);
    drawCube(1.0f, office_desk_texture);
    glPopMatrix();
    
    //parte superior da mesa 
    glPushMatrix();
    glTranslatef(x+0.5, 0.7f, z);
    glScalef(1.5, 0.1, 1.0);
    drawCube(1.0f, office_desk_texture);
    glPopMatrix();
}

void drawProjector() {
	int projector_texture[] = {-1, -1, -1, 4, -1, -1};
	
	glColor3f(1.0f, 1.0f, 1.0f);
	//suporte projetor
    glPushMatrix();
    glTranslatef(2.0f, 5.375f, -29.0);
    glScalef(0.05, 0.5, 0.05);
    glutSolidCube(1.0f);
    glPopMatrix();
    
	//projetor
    glPushMatrix();
    glTranslatef(2.0f, 5.0625f, -29.0f);
    glScalef(0.5, 0.125, 0.5);
    drawCube(1.0f, projector_texture);
    glPopMatrix();
}

void drawAirConditioning(float x, float z, char side) {
	//area de projeção
	int air_texture[] = {3, -1, -1, -1, -1, -1};
	
	if(side == 'r') {
		air_texture[0] = 3;
	} else if(side == 'l') {
		air_texture[2] = 3;
	}
	
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(x, 3.25f, z);
    glScalef(0.25, 0.5, 1.5);
    drawCube(1.0f, air_texture);
    glPopMatrix();
}

void drawProjectionQuad() {
	int projection_texture[] = {5, -1, -1, -1, -1, -1, -1};
	
    //bordas quadro
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(6.95f, 4.0f, -29.0f);
    glScalef(0.1, 2.0, 2.0);
    glutSolidCube(1.0f);
    glPopMatrix();

	glColor3f(1.0f, 1.0f, 1.0f);
	//area de projeção
    glPushMatrix();
    glTranslatef(6.85f, 4.0f, -29.0f);
    glScalef(0.1, 1.75, 1.75);
    drawCube(1.0f, projection_texture);
    glPopMatrix();
}

void drawChair(float x, float z) {
    glColor3f(0.1f, 0.0f, 0.0f);
    
    int chair_texture[] = {2, 2, 2, 2, 2, 2};
    
    //base esquerda
    glPushMatrix();
    glTranslatef(x, 0.125f, z);
    glScalef(0.25, 0.25, 1.0);
    drawCube(1.0f, chair_texture);
    glPopMatrix();

	//lateral esquerda
	glPushMatrix();
    glTranslatef(x, 0.5f, z);
    glScalef(0.125, 0.5f, 0.8);
    drawCube(1.0f, chair_texture);
    glPopMatrix();
    
    //suporte esquerdo do apoio traseiro
    glPushMatrix();
    glTranslatef(x, 0.875f, z+0.45);
    glScalef(0.1, 1.25f, 0.1);
    drawCube(1.0f, chair_texture);
    glPopMatrix();
    
    //base direita
    glPushMatrix();
    glTranslatef(x+2, 0.125f, z);
    glScalef(0.25, 0.25, 1.0);
    drawCube(1.0f, chair_texture);
    glPopMatrix();    
    
    //lateral direita
	glPushMatrix();
    glTranslatef(x+2, 0.5f, z);
    glScalef(0.125, 0.5f, 0.8);
    drawCube(1.0f, chair_texture);
    glPopMatrix();
    
    //acento 
    glPushMatrix();
    glTranslatef(x+1, 0.6f, z);
    glScalef(2.0, 0.1, 1.0);
    drawCube(1.0f, chair_texture);
    glPopMatrix();
    
    //suporte direito do apoio traseiro
    glPushMatrix();
    glTranslatef(x+2, 0.875f, z+0.45);
    glScalef(0.1, 1.25f, 0.1);
    drawCube(1.0f, chair_texture);
    glPopMatrix();
    
    //suporte das costas
    glPushMatrix();
    glTranslatef(x+1.0f, 1.125f, z+0.45);
    glScalef(2.25f, 0.75f, 0.1);
    drawCube(1.0f, chair_texture);
    glPopMatrix();
}

void drawTower() {
//Desenha a pilastra da cruz
  int inferior_cruz_texture[] = {-1, -1, -1, -1, 11, -1};
  int superior_cruz_texture[] = {-1, -1, -1, -1, 12, -1};

  glPushMatrix();
  glTranslatef(0.0f, 1.25f, -7.0f);
  glScalef(1.0f, 3.5f, 1.0f);
  glutSolidCube(0.5);
  glPopMatrix();
  
  //inferior
  glPushMatrix();
  glTranslatef(0.0f, 3.6f, -7.0f);
  glScalef(1.0f, 4.0f, 1.0f);
  drawCube(0.5f, inferior_cruz_texture);
  glPopMatrix();
  
  //superior
  glPushMatrix();
  glTranslatef(0.0f, 6.10f, -7.0f);
  glScalef(1.0f, 6.0f, 1.0f);
  drawCube(0.5f, superior_cruz_texture);
  glPopMatrix();
//####

  int base_texture[] = {-1, 1, -1, -1, -1, -1};

//Desenha a base da cruz
  glPushMatrix();
  glTranslatef(0.0f, 0.25f, -7.0f);
  glScalef(1.0, 0.25, 1.0);
  drawCube(2.0f, base_texture);
  glPopMatrix();

//Desenha a barra central da cruz
  glPushMatrix();
  glTranslatef(0.0f, 5.0f, -7.15f);
  glScalef(4.0, 0.25, 1.0);
  glutSolidCube(0.5);
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(0.0f, 4.5f, -6.55f);
  glScalef(1.0, 0.25, 1.0);
  glutSolidCube(0.5);
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(0.0f, 7.5f, -7.0f);
  glScalef(0.05f, 4.0f, 0.05f);
  glutSolidCube(1.0f);
  glPopMatrix();
}

//FIXME colocar aqui os outros componentes da entrada \/
void drawEntrance() {
	
  int fachada_letras_texture[] = {-1, -1, -1, -1, 6, -1};

//teta entrada
  glPushMatrix();
  glColor3f(1.0f, 1.0f, 1.0f);
  glTranslatef(0.0f, 2.25f, -5.5f);
  glScalef(15.0, 0.5, 1.0);
  drawCube(1.0f, fachada_letras_texture);
  glPopMatrix();
  
  glPushMatrix();
  glColor3f(1.0f, 1.0f, 1.0f);
  glTranslatef(0.0f, 2.25f, -7.5f);
  glScalef(15.0, 0.5, 3.0);
  glutSolidCube(1.0f);
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
    glTranslatef(3.25f, 1.25f, -9.25f);
    glScalef(17.0, 5.0, 1.0);
    glutSolidCube(0.5);
    glPopMatrix();

//Desenha parede frontal da esquerda da entreda
    glPushMatrix();
    glTranslatef(-5.0f, 1.25f, -9.25f);
    glScalef(10.0, 5.0, 1.0);
    glutSolidCube(0.5);
    glPopMatrix();

//Desenha parede direita do L da porta direita da entreda
    glPushMatrix();
    glTranslatef(-0.75f, 2.75f, -11.0f);
    glScalef(0.5, 5.5, 3.0);
    glutSolidCube(1.0);
    glPopMatrix();

//parede superior entrada (colocar textura)
	int fachada_teto_texture[] = {-1, -1, -1, -1, 10, -1};

    glPushMatrix();
    glTranslatef(0.0f, 4.25f, -9.25f);
    glScalef(15.0, 3.5, 0.5);
    drawCube(1.0f, fachada_teto_texture);
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
    glTranslatef(-7.25f, 2.75f, -20.5f);
    glScalef(0.5, 5.5, 22.0);
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
    glTranslatef(-5.45f, 2.75f, -17.25f);
    glScalef(3.13, 5.5, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

//parede lateral direita do templo
    glPushMatrix();
    glColor3f(0.66f,0.66f,0.66f);
    glTranslatef(7.25f, 2.75f, -20.5f);
    glScalef(0.5, 5.5, 22.0);
    glutSolidCube(1.0);
    glPopMatrix();

//parede do fundo do templo
    glPushMatrix();
    glColor3f(0.66f,0.66f,0.66f);
    glTranslatef(4.0f, 2.75f, -31.75f);
    glScalef(7.0, 5.5, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.66f,0.66f,0.66f);
    glTranslatef(-3.25f, 3.25f, -31.75f);
    glScalef(7.5, 0.5, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    
	glPushMatrix();
	glColor4f(0.5f,0.5f,0.5f, glass_alpha);
	glTranslatef(-1.5f, 1.5f, -31.75f);
    glScalef(4.0, 3.0, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
	glColor4f(0.5f,0.5f,0.5f, glass_alpha);
	glTranslatef(-1.5f, 4.5f, -31.75f);
    glScalef(4.0, 2.0, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
	glColor3f(0.66f,0.66f,0.66);
	glTranslatef(-3.75f, 2.75f, -31.75f);
    glScalef(0.5, 5.5, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
	glColor4f(0.5f,0.5f,0.5f, glass_alpha);
	glTranslatef(-5.5f, 1.5f, -31.75f);
    glScalef(3.0, 3.0, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
	glColor4f(0.5f,0.5f,0.5f, glass_alpha);
	glTranslatef(-5.5f, 4.5f, -31.75f);
    glScalef(3.0, 2.0, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
	glColor3f(0.66f,0.66f,0.66);
	glTranslatef(-7.25f, 2.75f, -31.75f);
    glScalef(0.5, 5.5, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

//teto do templo
    glPushMatrix();
    glColor3f(0.66f,0.66f,0.66f);
    glTranslatef(0.0f, 5.75f, -20.75f);
    glScalef(15.0, 0.5, 22.5);
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
    glTranslatef(-5.565f, 3.0f, -13.25f);
    glScalef(2.875, 1.0, 7.5);
    glutSolidCube(1.0);
    glPopMatrix();

//púlpito
	int pulpito_texture[] = {0, 0, 0, -1, 0, 0};
    glPushMatrix();
    glColor3f(0.66f,0.66f,0.66f);
    glTranslatef(4.75f, 0.75f, -26.75f);
    glScalef(4.5, 1.5, 0.5);
    drawCube(1.0, pulpito_texture);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.66f,0.66f,0.66f);
    glTranslatef(2.25f, 0.75f, -29.25f);
    glScalef(0.5, 1.5, 4.5);
    drawCube(1.0, pulpito_texture);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.66f,0.66f,0.66f);
    glTranslatef(2.25f, 0.75f, -26.75f);
    glScalef(0.5, 1.5, 0.5);
    drawCube(1.0, pulpito_texture);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.66f,0.66f,0.66f);
    glTranslatef(4.75f, 0.75f, -29.25f);
    glScalef(4.5, 1.5, 4.5);
    drawCube(1.0, pulpito_texture); 
    glPopMatrix();
    
//escadas frontais
    glPushMatrix();
    glColor3f(0.66f,0.66f,0.66f);
    glTranslatef(4.5f, 0.5f, -26.25f);
    glScalef(5.0, 1.0, 0.5);
    drawCube(1.0, pulpito_texture);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.66f,0.66f,0.66f);
    glTranslatef(1.75f, 0.5f, -26.25f);
    glScalef(0.5, 1.0, 0.5);
    drawCube(1.0, pulpito_texture);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.66f,0.66f,0.66f);
    glTranslatef(4.25f, 0.25f, -25.75f);
    glScalef(5.5, 0.5, 0.5);
    drawCube(1.0, pulpito_texture);
    glPopMatrix();
    
//escadas laterais
    glPushMatrix();
    glColor3f(0.66f,0.66f,0.66f);
    glTranslatef(1.75f, 0.5f, -29.0f);
    glScalef(0.5, 1.0, 5.0);
    drawCube(1.0, pulpito_texture);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.66f,0.66f,0.66f);
    glTranslatef(1.25f, 0.25f, -28.75f);
    glScalef(0.5, 0.5, 5.5);
    drawCube(1.0, pulpito_texture);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.66f,0.66f,0.66f);
    glTranslatef(1.25f, 0.25f, -25.75f);
    glScalef(0.5, 0.5, 0.5);
    drawCube(1.0, pulpito_texture);
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

  //piso-templo
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, texture_id[7]);	 
  glTranslatef(0.0f, 0.0f, -13.0f);
  glBegin(GL_QUADS);
  glColor3f(1.0f, 1.0f, 1.0f);
  glTexCoord2f(0.0f, 1.0f); 
  glVertex3f(-7.5f, 0.0f, -19.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-7.5f, 0.0f, 7.5f);
  glTexCoord2f(1.0f, 0.0f); 
  glVertex3f( 7.5f, 0.0f, 7.5f);
  glTexCoord2f(1.0f, 1.0f); 
  glVertex3f( 7.5f, 0.0f, -19.0f);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);	 
  glPopMatrix();
  
  //gramado lado esquerdo
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, texture_id[1]);	 
  glTranslatef(-5.0f, 0.0f, 6.25f);
  glBegin(GL_QUADS);
  glColor3f(1.0f, 1.0f, 1.0f);
  glTexCoord2f(0.0f, 1.0f); 
  glVertex3f(-2.5f, 0.0f, -11.75f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-2.5f, 0.0f, 2.5f);
  glTexCoord2f(1.0f, 0.0f); 
  glVertex3f( 2.5f, 0.0f, 2.5f);
  glTexCoord2f(1.0f, 1.0f); 
  glVertex3f( 2.5f, 0.0f, -11.75f);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);	 
  glPopMatrix();
  
  //gramado lado direito
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, texture_id[1]);	 
  glTranslatef(3.25f, 0.0f, 4.5f);
  glBegin(GL_QUADS);
  glColor3f(1.0f, 1.0f, 1.0f);
  glTexCoord2f(0.0f, 1.0f); 
  glVertex3f(-4.25f, 0.0f, -10.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-4.25f, 0.0f, 4.25f);
  glTexCoord2f(1.0f, 0.0f); 
  glVertex3f( 4.25f, 0.0f, 4.25f);
  glTexCoord2f(1.0f, 1.0f); 
  glVertex3f( 4.25f, 0.0f, -10.0f);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);	 
  glPopMatrix();
  
  //piso entrada
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, texture_id[8]);	 
  glTranslatef(-1.75f, 0.0f, 4.5f);
  glBegin(GL_QUADS);
  glColor3f(1.0f, 1.0f, 1.0f);
  glTexCoord2f(0.0f, 1.0f); 
  glVertex3f(-0.75f, 0.0f, -10.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-0.75f, 0.0f, 4.25f);
  glTexCoord2f(1.0f, 0.0f); 
  glVertex3f( 0.75f, 0.0f, 4.25f);
  glTexCoord2f(1.0f, 1.0f); 
  glVertex3f( 0.75f, 0.0f, -10.0f);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);	 
  glPopMatrix();
}

void test() {
	int texture[] = {-1, //esquerda
					 -1, //cima
					 -1, //direita 
					 -1, //baixo
					 -1, //frente
					 -1}; //tras

	glPushMatrix();
	glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
	glTranslatef(0.0f, 2.0f, 0.0f);
	drawCube(2, texture);
	glPopMatrix();
}

void display()
{
  // Clear Color and Depth Buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // To operate on model-view matrix
  glMatrixMode(GL_MODELVIEW);     
  // Reset transformations
  glLoadIdentity();
  // Set the camera
  gluLookAt(  x, y, z,
  x+lx, y, z+lz,
  0.0f, 1.0f, 0.0f);

  //~ glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  drawChair(3.0f, -12.0f);
  drawChair(3.0f, -14.0f);
  drawChair(3.0f, -16.0f);
  drawChair(3.0f, -18.0f);
  drawChair(3.0f, -20.0f);
  drawChair(3.0f, -22.0f);
  
  drawChair(-2.0f, -22.0f);
  drawChair(-2.0f, -20.0f);
  drawChair(-2.0f, -18.0f);
  drawChair(-2.0f, -16.0f);
  
  drawChair(-6.0f, -25.0f);
  drawChair(-6.0f, -23.0f);
  drawChair(-6.0f, -21.0f);
  drawChair(-6.0f, -19.0f);
  
  drawFloor();
  drawTower();
  drawEntrance();
  drawTemple();
  drawDoor();
  drawProjectionQuad();
  drawProjector();
  drawOfficeDesk(-6.0f, -10.5f);
  drawAirConditioning(6.85, -22.0, 'r');
  drawAirConditioning(6.85, -18.0, 'r');
  drawAirConditioning(6.85, -14.0, 'r');
  
  drawAirConditioning(-6.85, -28.0, 'l');
  drawAirConditioning(-6.85, -25.0, 'l');
  drawAirConditioning(-6.85, -22.0, 'l');
  //~ test();
  
  glFlush();
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

float fraction = 0.5f;
float fraction_2 = 0.1f;

  switch (key)
  {
    case GLUT_KEY_LEFT :
    angle -= 0.05f;
    lx = sin(angle);
    lz = -cos(angle);
    break;
    case GLUT_KEY_RIGHT :
    angle += 0.05f;
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
    case GLUT_KEY_PAGE_UP:
    y += y * fraction_2;
    break;
    case GLUT_KEY_PAGE_DOWN:
    y -= y * fraction_2;
    break;
  }
}

void loadTextureFromFile(char const *filename,int index) {
  int width, height, c;
  c = 3;
  std::ifstream file(filename);
  if(! file.good())
    throw "file not found";
  file.close();

sf::Image image;
image.loadFromFile(filename);

    printf("%d %d\n", width, height);

  glGenTextures(1, &texture_id[index]);
  glBindTexture(GL_TEXTURE_2D, texture_id[index]);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
  glBindTexture(GL_TEXTURE_2D, 0);
}

void initTextures(){
	loadTextureFromFile("texture/piso-escada.jpg", 0);
	loadTextureFromFile("texture/grass.jpg", 1);
	loadTextureFromFile("texture/tabaco.jpg", 2);
	loadTextureFromFile("texture/airc.jpg", 3);
	loadTextureFromFile("texture/projetor.jpg", 4);
	loadTextureFromFile("texture/slide_projetor.png", 5);
	loadTextureFromFile("texture/fachada-lt.png", 6);
	loadTextureFromFile("texture/piso-templo.jpg", 7);
	loadTextureFromFile("texture/piso-entrada.jpg", 8);
	loadTextureFromFile("texture/mesa.jpg", 9);
	loadTextureFromFile("texture/fachada-teto.png", 10);
	loadTextureFromFile("texture/inferior-cruz.png", 11);
	loadTextureFromFile("texture/superior-cruz.png", 12);
	
}
	
void init() {
  glClearColor(0.0, 0.0, 0.0, 0.0);

  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  glEnable(GL_COLOR_MATERIAL);

  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 
  glEnable(GL_TEXTURE_2D);
 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);

  initTextures();
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
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
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

  //glutIdleFunc(animate);
  glutMainLoop();

  return 0;
}
