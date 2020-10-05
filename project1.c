/*
 * template.c
 *
 * An OpenGL source code template.
 */


#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <stdio.h>
#include <math.h>

#include "initShader.h"
#include "mylib.h"


#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))
#define CONVERT_TO_RADIANS M_PI/180
void genVertices();
void genColors();

vec4 vertices[950];
vec4 colors[950];

//1 triangle every 5 degrees makes a smooth looking circle = 360/5 triangles = 72 triangles
//2*72 for the top part of the cone = 144
//144 triangles * 3 vertices per triangle = 432
int num_vertices = 950;
int vertexCount = 0;

float degrees = 0;

GLuint ctm_location;
mat4 ctm = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
mat4 currentScale = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

float scalingFactor = 1.0;

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

    ctm_location = glGetUniformLocation(program, "ctm");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glDepthRange(1,0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);

    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ctm);

    glDrawArrays(GL_TRIANGLES, 0, num_vertices);

    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, 512, 512);
}

void genVertices()
{
  //make bottom circle
  //get circle working first
  int j = 0;
  for(int i=0; i<360; i+=360/72)
  {
    vertices[j].x = 0.0;
    vertices[j].z = 0.0;
    vertices[j].y = 0.0;
    vertices[j].w = 1.0;

    j++;

    vertices[j].x = cos(i*CONVERT_TO_RADIANS);
    vertices[j].z = sin(i*CONVERT_TO_RADIANS);
    vertices[j].y = 0.0;
    vertices[j].w = 1.0;

    j++;

    vertices[j].x = cos((i+(360/72))*CONVERT_TO_RADIANS);
    vertices[j].z = sin((i+(360/72))*CONVERT_TO_RADIANS);
    vertices[j].y = 0.0;
    vertices[j].w = 1.0;

    j++;
  }
  //make top part
  int i=0;
  for(; j<num_vertices; j++)
  {
    if(vertices[i].x == 0 && vertices[i].y == 0 && vertices[i].z == 0)
    {
      vertices[j].x = 0.0;
      vertices[j].y = 1.0;
      vertices[j].z = 0.0;
      vertices[j].w = 1.0;
    }
    else
    {
      vertices[j].x = vertices[i].x;
      vertices[j].y = vertices[i].y;
      vertices[j].z = vertices[i].z;
      vertices[j].w = 1.0;
    }
    i++;
  }
}

void genSphere()
{
  for(float phiDeg = 0; phiDeg <= 180; phiDeg+=20)
  {
    float phi = phiDeg*CONVERT_TO_RADIANS;
    float nextPhi = (phiDeg + 10) * CONVERT_TO_RADIANS;
    for(float thetaDeg=0; thetaDeg<=360; thetaDeg+=20)
    {
      float theta = thetaDeg*CONVERT_TO_RADIANS;
      float nextTheta = (thetaDeg+20)*CONVERT_TO_RADIANS;

      vertices[vertexCount].x = cos(phi)*cos(theta);
      vertices[vertexCount].y = cos(phi)*sin(theta);
      vertices[vertexCount].z = sin(phi);
      vertices[vertexCount].w = 1;

      vertexCount++;

      vertices[vertexCount].x = sin(nextPhi)*cos(theta);
      vertices[vertexCount].y = sin(nextPhi)*sin(theta);
      vertices[vertexCount].z = sin(nextPhi);
      vertices[vertexCount].w = 1;

      vertexCount++;

      vertices[vertexCount].x = sin(nextPhi)*cos(nextTheta);
      vertices[vertexCount].y = sin(nextPhi)*sin(nextTheta);
      vertices[vertexCount].z = sin(nextPhi);
      vertices[vertexCount].w = 1;

      vertexCount++;

      vertices[vertexCount].x = cos(phi)*cos(theta);
      vertices[vertexCount].y = cos(phi)*sin(theta);
      vertices[vertexCount].z = sin(phi);
      vertices[vertexCount].w = 1;

      vertexCount++;

      vertices[vertexCount].x = sin(nextPhi)*cos(nextTheta);
      vertices[vertexCount].y = sin(nextPhi)*sin(nextTheta);
      vertices[vertexCount].z = sin(nextPhi);
      vertices[vertexCount].w = 1;

      vertexCount++;

      vertices[vertexCount].x = sin(phi)*cos(nextTheta);
      vertices[vertexCount].y = sin(phi)*sin(nextTheta);
      vertices[vertexCount].z = sin(phi);
      vertices[vertexCount].w = 1;

      }
    }
    printf("%d\n", vertexCount);
}

void genColors()
{
  for(int i=0; i<num_vertices; i++)
  {
    colors[i].x = (double)rand() / RAND_MAX;
    colors[i].y = (double)rand() / RAND_MAX;
    colors[i].z = (double)rand() / RAND_MAX;
    colors[i].w = 1.0;
  }
}

void keyboard(unsigned char key, int mousex, int mousey)
{
    if(key == 'q')
    	glutLeaveMainLoop();

    //glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
  if(button == 3)
  {
    scalingFactor *= 1.2;
    currentScale = mat4_scale(scalingFactor, scalingFactor, scalingFactor);
    ctm = mat4_scale(scalingFactor, scalingFactor, scalingFactor);
  }
  else if(button == 4)
  {
    scalingFactor /= 1.2;
    currentScale = mat4_scale(scalingFactor, scalingFactor, scalingFactor);
    ctm = mat4_scale(scalingFactor, scalingFactor, scalingFactor);
  }
  glutPostRedisplay();
}

void motion(int x, int y)
{
  float glx = x;
  float gly = y;

    glx = ((glx/256)-1);
    gly = -((gly/256)-1);

    vec4 v = {glx, gly, 0, 0};

    v = vec4_norm(v);
    float d = pow(pow(v.y, 2) + pow(v.z, 2), 0.5);
    float sintx = v.y/d;
    float costx = v.z/d;

    mat4 rxtx = {{1, 0, 0, 0}, {0, costx, sintx, 0}, {0, -sintx, costx, 0}, {0, 0, 0, 1}};
    mat4 rxnegativetx = mat4_trans(rxtx);

    float sinty = v.x;
    float costy = d;

    mat4 rynegativety = {{costy, 0, sinty, 0}, {0, 1, 0, 0}, {-sinty, 0, costy, 0}, {0, 0, 0, 1}};
    mat4 ryty = mat4_trans(rynegativety);


    mat4 M1 = mat4_mult(rynegativety, rxtx);
    mat4 M2 = mat4_mult(mat4_rotate_z(45*CONVERT_TO_RADIANS), M1);
    mat4 M3 = mat4_mult(ryty, M2);
    mat4 R = mat4_mult(rxnegativetx, M3);
    ctm = mat4_mult(R, currentScale);


  glutPostRedisplay();
}

void idle()
{
  glutPostRedisplay();
}

int main(int argc, char **argv)
{
    //genVertices();
    genSphere();
    genColors();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Project 1");
    glewInit();
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}
