/*
 * template.c
 *
 * An OpenGL source code template.
 */


#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "initShader.h"
#include "mylib.h"


#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))
#define CONVERT_TO_RADIANS M_PI/180
void genVertices();
void genColors();

vec4 vertices[7776];
vec4 colors[7776];

//1 triangle every 5 degrees makes a smooth looking circle = 360/5 triangles = 72 triangles
//2*72 for the top part of the cone = 144
//144 triangles * 3 vertices per triangle = 432
int num_vertices = 7776;
int vertexCount = 0;

typedef struct
{
  int north;
  int south;
  int east;
  int west;
} cell;

cell walls[8][8];
int visited[8][8];

void init(void)
{

    GLuint program = initShader("vshader.glsl", "fshader.glsl");
    glUseProgram(program);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);

    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    GLuint vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *) sizeof(vertices));

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glDepthRange(1,0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);

    glDrawArrays(GL_TRIANGLES, 0, num_vertices);

    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, 512, 512);
}

void keyboard(unsigned char key, int mousex, int mousey)
{
    if(key == 'q')
    	glutLeaveMainLoop();

    //glutPostRedisplay();
}

void idle()
{
  glutPostRedisplay();
}

int allNeighborsVisited(int row, int col)
{
  //check neighbor to south
  if(row+1 <= 7)
  {
    if(visited[row+1][col] != 1)
      return 0;
  }
  if(row-1 >= 0)
  {
    if(visited[row-1][col] != 1)
      return 0;
  }
  if(col+1 <= 7)
  {
    if(visited[row][col+1] != 1)
      return 0;
  }
  if(col-1 >= 0)
  {
    if(visited[row][col-1] != 1)
      return 0;
  }

  return 1;
}

int generateMaze(int row, int col)
{
  visited[row][col] = 1;
  int nrow = row;
  int ncol = col;
  int good = 0;

  if(allNeighborsVisited(row, col) == 1)
    return -1;

  do
  {
    switch(rand() % 4)
    {
      //0=south, 1=east, 2=north, 3=west
      case 0:
        nrow = row+1;
        ncol = col;
        if(nrow < 8 && visited[nrow][ncol]==0)
        {
          //printf("I'm going south\n");
          walls[row][col].south = 0;
          walls[nrow][ncol].north = 0;
          good = 1;
        }
        break;

      case 1:
        nrow = row;
        ncol = col + 1;
        if(ncol < 8 && visited[nrow][ncol] == 0)
        {
          //printf("I'm going east\n");
          walls[row][col].east = 0;
          walls[nrow][ncol].west = 0;
          good = 1;
        }
        break;

      case 2:
        nrow = row-1;
        ncol = col;
        if(nrow >=0 && visited[nrow][ncol] == 0)
        {
          //printf("I'm going north\n");
          walls[row][col].north = 0;
          walls[nrow][ncol].south = 0;
          good = 1;
        }
        break;

      case 3:
        nrow = row;
        ncol = col - 1;
        if(ncol >= 0 && visited[nrow][ncol] == 0)
        {
          //printf("I'm going west\n");
          walls[row][col].west = 0;
          walls[nrow][ncol].east = 0;
          good = 1;
        }
        break;
    }
  }while(good == 0);

  if(generateMaze(nrow, ncol) == -1 && !allNeighborsVisited(row, col))
    generateMaze(row, col);
  else if(allNeighborsVisited(row, col))
    return -1;

  return 0;
}

void fillArrays()
{
  for(int i = 0; i<8; i++)
    for(int j = 0; j<8; j++)
    {
      walls[i][j].north = 1;
      walls[i][j].south = 1;
      walls[i][j].east = 1;
      walls[i][j].west = 1;
      visited[i][j] = 0;
    }
}

void printMaze()
{
  printf("▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n");
  for(int i = 0; i<8; i++)
  {
    for(int j=0; j<8; j++)
    {
      if(j == 0)
      {
        if(i!=0)
          printf("│");
        else
          printf(" ");
        if(walls[i][j].south == 1)
          printf("▁");
        else
          printf(" ");
      }
      else if(j == 7)
      {
        if(walls[i][j].south == 1)
          printf("▁");
        else
          printf(" ");
        if(i == 7)
          printf(" ");
        else
          printf("│");
      }
      else
      {
        if(walls[i][j].west == 1)
          printf("│");
        else
          printf("▁");
        if(walls[i][j].south == 1)
          printf("▁");
        else
          printf(" ");
      }

    }
    printf("\n");
  }
}

int main(int argc, char **argv)
{
    fillArrays();
    time_t t;
    srand((unsigned) time(&t));
    generateMaze(rand()%8, rand()%8);
    walls[0][0].west = 0;
    walls[7][7].east = 0;
    printMaze();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Project 2");
    glewInit();
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}
