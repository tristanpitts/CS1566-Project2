#ifndef _MYLIB_H_
#define _MYLIB_H_

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  float x;
  float y;
  float z;
  float w;
} vec4;

typedef struct
{
  vec4 x;
  vec4 y;
  vec4 z;
  vec4 w;
} mat4;

void vec4_print(vec4 v);
vec4 vec4_smult(vec4 v, float s);
vec4 vec4_add(vec4 v1, vec4 v2);
vec4 vec4_sub(vec4 v1, vec4 v2);
float vec4_mag(vec4 v);
vec4 vec4_norm(vec4 v);
float vec4_dot(vec4 v1, vec4 v2);
vec4 vec4_cross(vec4 v1, vec4 v2);

void mat4_print(mat4 m);
mat4 mat4_smult(mat4 m, float s);
mat4 mat4_add(mat4 m1, mat4 m2);
mat4 mat4_sub(mat4 m1, mat4 m2);
mat4 mat4_mult(mat4 m1, mat4 m2);
mat4 mat4_inv(mat4 m);
mat4 mat4_minor(mat4 m);
mat4 mat4_cofactor(mat4 m);
mat4 mat4_trans(mat4 m);
float mat4_det(mat4 m);
vec4 mat4_vmult(mat4 m, vec4 v);

mat4 mat4_translate(float x, float y, float z);
mat4 mat4_scale(float x, float y, float z);
mat4 mat4_rotate_x(float theta);
mat4 mat4_rotate_y(float theta);
mat4 mat4_rotate_z(float theta);

#endif
