#include "mylib.h"

void vec4_print(vec4 v)
{
  printf("[%f %f %f %f]\n\n", v.x, v.y, v.z, v.w);
}

vec4 vec4_smult(vec4 v, float s)
{
  v.x = v.x * s;
  v.y = v.y * s;
  v.z = v.z * s;
  v.w = v.w * s;
  return v;
}

vec4 vec4_add(vec4 v1, vec4 v2)
{
  vec4* result = (vec4*)malloc(sizeof(vec4));

  result->x = v1.x + v2.x;
  result->y = v1.y + v2.y;
  result->z = v1.z + v2.z;
  result->w = v1.w + v2.w;

  return * result;
}

vec4 vec4_sub(vec4 v1, vec4 v2)
{
  vec4* result = (vec4*)malloc(sizeof(vec4));

  result->x = v1.x - v2.x;
  result->y = v1.y - v2.y;
  result->z = v1.z - v2.z;
  result->w = v1.w - v2.w;

  return * result;
}

float vec4_mag(vec4 v)
{
  return pow(pow(v.x,2) + pow(v.y,2) + pow(v.z,2) + pow(v.w, 2),0.5);
}

vec4 vec4_norm(vec4 v)
{
  float m = vec4_mag(v);

  vec4* result = (vec4*)malloc(sizeof(vec4));

  result->x = v.x/m;
  result->y = v.y/m;
  result->z = v.z/m;
  result->w = v.w/m;

  return * result;
}

float vec4_dot(vec4 v1, vec4 v2)
{
  return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z + v1.w*v2.w;
}

vec4 vec4_cross(vec4 v1, vec4 v2)
{
  vec4* result = (vec4*)malloc(sizeof(vec4));

  result->x = (v1.y * v2.z) - (v1.z * v2.y);
  result->y = (v1.z * v2.x) - (v1.x * v2.z);
  result->z = (v1.x * v2.y) - (v1.y * v2.x);
  result->w = 0;

  return * result;
}

void mat4_print(mat4 m)
{
  printf("┏ %f %f %f %f\n", m.x.x, m.y.x, m.z.x, m.w.x);
  printf("┃ %f %f %f %f\n", m.x.y, m.y.y, m.z.y, m.w.y);
  printf("┃ %f %f %f %f\n", m.x.z, m.y.z, m.z.z, m.w.z);
  printf("┗ %f %f %f %f\n\n", m.x.w, m.y.w, m.z.w, m.w.w);
}

mat4 mat4_smult(mat4 m, float s)
{
  mat4* result = (mat4*)malloc(sizeof(mat4));

  result->x = vec4_smult(m.x, s);
  result->y = vec4_smult(m.y, s);
  result->z = vec4_smult(m.z, s);
  result->w = vec4_smult(m.w, s);

  return * result;
}

mat4 mat4_add(mat4 m1, mat4 m2)
{
  mat4* result = (mat4*)malloc(sizeof(mat4));

  result->x = vec4_add(m1.x, m2.x);
  result->y = vec4_add(m1.y, m2.y);
  result->z = vec4_add(m1.z, m2.z);
  result->w = vec4_add(m1.w, m2.w);

  return * result;
}

mat4 mat4_sub(mat4 m1, mat4 m2)
{
  mat4* result = (mat4*)malloc(sizeof(mat4));

  result->x = vec4_sub(m1.x, m2.x);
  result->y = vec4_sub(m1.y, m2.y);
  result->z = vec4_sub(m1.z, m2.z);
  result->w = vec4_sub(m1.w, m2.w);

  return * result;
}

mat4 mat4_mult(mat4 m1, mat4 m2)
{
  mat4* result = (mat4*)malloc(sizeof(mat4));

  result->x.x = (m1.x.x * m2.x.x) + (m1.y.x * m2.x.y) + (m1.z.x * m2.x.z) + (m1.w.x * m2.x.w);
  result->x.y = (m1.x.y * m2.x.x) + (m1.y.y * m2.x.y) + (m1.z.y * m2.x.z) + (m1.w.y * m2.x.w);
  result->x.z = (m1.x.z * m2.x.x) + (m1.y.z * m2.x.y) + (m1.z.z * m2.x.z) + (m1.w.z * m2.x.w);
  result->x.w = (m1.x.w * m2.x.x) + (m1.y.w * m2.x.y) + (m1.z.w * m2.x.z) + (m1.w.w * m2.x.w);

  result->y.x = (m1.x.x * m2.y.x) + (m1.y.x * m2.y.y) + (m1.z.x * m2.y.z) + (m1.w.x * m2.y.w);
  result->y.y = (m1.x.y * m2.y.x) + (m1.y.y * m2.y.y) + (m1.z.y * m2.y.z) + (m1.w.y * m2.y.w);
  result->y.z = (m1.x.z * m2.y.x) + (m1.y.z * m2.y.y) + (m1.z.z * m2.y.z) + (m1.w.z * m2.y.w);
  result->y.w = (m1.x.w * m2.y.x) + (m1.y.w * m2.y.y) + (m1.z.w * m2.y.z) + (m1.w.w * m2.y.w);

  result->z.x = (m1.x.x * m2.z.x) + (m1.y.x * m2.z.y) + (m1.z.x * m2.z.z) + (m1.w.x * m2.z.w);
  result->z.y = (m1.x.y * m2.z.x) + (m1.y.y * m2.z.y) + (m1.z.y * m2.z.z) + (m1.w.y * m2.z.w);
  result->z.z = (m1.x.z * m2.z.x) + (m1.y.z * m2.z.y) + (m1.z.z * m2.z.z) + (m1.w.z * m2.z.w);
  result->z.w = (m1.x.w * m2.z.x) + (m1.y.w * m2.z.y) + (m1.z.w * m2.z.z) + (m1.w.w * m2.z.w);

  result->w.x = (m1.x.x * m2.w.x) + (m1.y.x * m2.w.y) + (m1.z.x * m2.w.z) + (m1.w.x * m2.w.w);
  result->w.y = (m1.x.y * m2.w.x) + (m1.y.y * m2.w.y) + (m1.z.y * m2.w.z) + (m1.w.y * m2.w.w);
  result->w.z = (m1.x.z * m2.w.x) + (m1.y.z * m2.w.y) + (m1.z.z * m2.w.z) + (m1.w.z * m2.w.w);
  result->w.w = (m1.x.w * m2.w.x) + (m1.y.w * m2.w.y) + (m1.z.w * m2.w.z) + (m1.w.w * m2.w.w);

  return * result;
}

mat4 mat4_minor(mat4 m)
{
  mat4* result = (mat4*)malloc(sizeof(mat4));

  result->x.x = m.y.y * (m.z.z*m.w.w - m.w.z*m.z.w) - m.y.z * (m.z.y*m.w.w - m.w.y*m.z.w) + m.y.w * (m.z.y*m.w.z - m.w.y*m.z.z);
  result->x.y = m.y.x * (m.z.z*m.w.w - m.w.z*m.z.w) - m.y.z * (m.z.x*m.w.w - m.w.x*m.z.w) + m.y.w * (m.z.x*m.w.z - m.w.x*m.z.z);
  result->x.z = m.y.x * (m.z.y*m.w.w - m.w.y*m.z.w) - m.y.y * (m.z.x*m.w.w - m.w.x*m.z.w) + m.y.w * (m.z.x*m.w.y - m.w.x*m.z.y);
  result->x.w = m.y.x * (m.z.y*m.w.z - m.w.y*m.z.z) - m.y.y * (m.z.x*m.w.z - m.w.x*m.z.z) + m.y.z * (m.z.x*m.w.y - m.w.x*m.z.y);

  result->y.x = m.x.y * (m.z.z*m.w.w - m.w.z*m.z.w) - m.x.z * (m.z.y*m.w.w - m.w.y*m.z.w) + m.x.w * (m.z.y*m.w.z - m.w.y*m.z.z);
  result->y.y = m.x.x * (m.z.z*m.w.w - m.w.z*m.z.w) - m.x.z * (m.z.x*m.w.w - m.w.x*m.z.w) + m.x.w * (m.z.x*m.w.z - m.w.x*m.z.z);
  result->y.z = m.x.x * (m.z.y*m.w.w - m.w.y*m.z.w) - m.x.y * (m.z.x*m.w.w - m.w.x*m.z.w) + m.x.w * (m.z.x*m.w.y - m.w.x*m.z.y);
  result->y.w = m.x.x * (m.z.y*m.w.z - m.w.y*m.z.z) - m.x.y * (m.z.x*m.w.z - m.w.x*m.z.z) + m.x.z * (m.z.x*m.w.y - m.w.x*m.z.y);

  result->z.x = m.x.y * (m.y.z*m.w.w - m.w.z*m.y.w) - m.x.z * (m.y.y*m.w.w - m.w.y*m.y.w) + m.x.w * (m.y.y*m.w.z - m.w.y*m.y.z);
  result->z.y = m.x.x * (m.y.z*m.w.w - m.w.z*m.y.w) - m.x.z * (m.y.x*m.w.w - m.w.x*m.y.w) + m.x.w * (m.y.x*m.w.z - m.w.x*m.y.z);
  result->z.z = m.x.x * (m.y.y*m.w.w - m.w.y*m.y.w) - m.x.y * (m.y.x*m.w.w - m.w.x*m.y.w) + m.x.w * (m.y.x*m.w.y - m.w.x*m.y.y);
  result->z.w = m.x.x * (m.y.y*m.w.z - m.w.y*m.y.z) - m.x.y * (m.y.x*m.w.z - m.w.x*m.y.z) + m.x.z * (m.y.x*m.w.y - m.w.x*m.y.y);

  result->w.x = m.x.y * (m.y.z*m.z.w - m.z.z*m.y.w) - m.x.z * (m.y.y*m.z.w - m.z.y*m.y.w) + m.x.w * (m.y.y*m.z.z - m.z.y*m.y.z);
  result->w.y = m.x.x * (m.y.z*m.z.w - m.z.z*m.y.w) - m.x.z * (m.y.x*m.z.w - m.z.x*m.y.w) + m.x.w * (m.y.x*m.z.z - m.z.x*m.y.z);
  result->w.z = m.x.x * (m.y.y*m.z.w - m.z.y*m.y.w) - m.x.y * (m.y.x*m.z.w - m.z.x*m.y.w) + m.x.w * (m.y.x*m.z.y - m.z.x*m.y.y);
  result->w.w = m.x.x * (m.y.y*m.z.z - m.z.y*m.y.z) - m.x.y * (m.y.x*m.z.z - m.z.x*m.y.z) + m.x.z * (m.y.x*m.z.y - m.z.x*m.y.y);

  return * result;
}

mat4 mat4_cofactor(mat4 m)
{
  mat4* result = (mat4*)malloc(sizeof(mat4));

  result->x.x = m.x.x;
  result->x.y = -1*m.x.y;
  result->x.z = m.x.z;
  result->x.w = -1*m.x.w;

  result->y.x = -1*m.y.x;
  result->y.y = m.y.y;
  result->y.z = -1*m.y.z;
  result->y.w = m.y.w;

  result->z.x = m.z.x;
  result->z.y = -1*m.z.y;
  result->z.z = m.z.z;
  result->z.w = -1*m.z.w;

  result->w.x = -1*m.w.x;
  result->w.y = m.w.y;
  result->w.z = -1*m.w.z;
  result->w.w = m.w.w;


  return * result;
}

mat4 mat4_trans(mat4 m)
{
  mat4* result = (mat4*)malloc(sizeof(mat4));

  result->x.x = m.x.x;
  result->y.x = m.x.y;
  result->z.x = m.x.z;
  result->w.x = m.x.w;

  result->x.y = m.y.x;
  result->y.y = m.y.y;
  result->z.y = m.y.z;
  result->w.y = m.y.w;

  result->x.z = m.z.x;
  result->y.z = m.z.y;
  result->z.z = m.z.z;
  result->w.z = m.z.w;

  result->x.w = m.w.x;
  result->y.w = m.w.y;
  result->z.w = m.w.z;
  result->w.w = m.w.w;

  return * result;
}

float mat4_det(mat4 m)
{
  float a = m.x.x * (m.y.y * (m.z.z*m.w.w - m.w.z*m.z.w) - m.y.z * (m.z.y*m.w.w - m.w.y*m.z.w) + m.y.w * (m.z.y*m.w.z - m.w.y*m.z.z));
  a = a - m.x.y * (m.y.x * (m.z.z*m.w.w - m.w.z*m.z.w) - m.y.z * (m.z.x*m.w.w - m.w.x*m.z.w) + m.y.w * (m.z.x*m.w.z - m.w.x*m.z.z));
  a = a + m.x.z * (m.y.x * (m.z.y*m.w.w - m.w.y*m.z.w) - m.y.y * (m.z.x*m.w.w - m.w.x*m.z.w) + m.y.w * (m.z.x*m.w.y - m.w.x*m.z.y));
  a = a - m.x.w * (m.y.x * (m.z.y*m.w.z - m.w.y*m.z.z) - m.y.y * (m.z.x*m.w.z - m.w.x*m.z.z) + m.y.z * (m.z.x*m.w.y - m.w.x*m.z.y));
  return a;
}

mat4 mat4_inv(mat4 m)
{
  mat4* result = (mat4*)malloc(sizeof(mat4));
  mat4 temp;

  temp = mat4_minor(m);
  temp = mat4_cofactor(temp);
  temp = mat4_trans(temp);
  float det = mat4_det(m);
  temp = mat4_smult(temp, (1/det));

  memcpy(result, &temp, sizeof(mat4));

  return * result;
}

vec4 mat4_vmult(mat4 m, vec4 v)
{
  vec4* result = (vec4*)malloc(sizeof(vec4));

  result->x = m.x.x * v.x + m.y.x * v.y + m.z.x * v.z + m.w.x * v.w;

  result->y = m.x.y * v.x + m.y.y * v.y + m.z.y * v.z + m.w.y * v.w;

  result->z = m.x.z * v.x + m.y.z * v.y + m.z.z * v.z + m.w.z * v.w;

  result->w = m.x.w * v.x + m.y.w * v.y + m.z.w * v.z + m.w.w * v.w;

  return * result;
}

mat4 mat4_translate(float x, float y, float z)
{
  mat4* result = (mat4*)malloc(sizeof(mat4));
  result->x.x = 1;
  result->x.y = 0;
  result->x.z = 0;
  result->x.w = 0;

  result->y.x = 0;
  result->y.y = 1;
  result->y.z = 0;
  result->y.w = 0;

  result->z.x = 0;
  result->z.y = 0;
  result->z.z = 1;
  result->z.w = 0;

  result->w.x = x;
  result->w.y = y;
  result->w.z = z;
  result->w.w = 1;

  return * result;
}

mat4 mat4_scale(float x, float y, float z)
{
  mat4* result = (mat4*)malloc(sizeof(mat4));
    result->x.x = x;
    result->y.x = 0;
    result->z.x = 0;
    result->w.x = 0;

    result->x.y = 0;
    result->y.y = y;
    result->z.y = 0;
    result->w.y = 0;

    result->x.z = 0;
    result->y.z = 0;
    result->z.z = z;
    result->w.z = 0;

    result->x.w = 0;
    result->y.w = 0;
    result->z.w = 0;
    result->w.w = 1;

  return * result;
}

mat4 mat4_rotate_x(float theta)
{
  mat4* result = (mat4*)malloc(sizeof(mat4));
  result->x.x = 1;
  result->y.x = 0;
  result->z.x = 0;
  result->w.x = 0;

  result->x.y = 0;
  result->y.y = cos(theta);
  result->z.y = -sin(theta);
  result->w.y = 0;

  result->x.z = 0;
  result->y.z = sin(theta);
  result->z.z = cos(theta);
  result->w.z = 0;

  result->x.w = 0;
  result->y.w = 0;
  result->z.w = 0;
  result->w.w = 1;

  return * result;
}

mat4 mat4_rotate_y(float theta)
{
  mat4* result = (mat4*)malloc(sizeof(mat4));
  result->x.x = cos(theta);
  result->y.x = 0;
  result->z.x = sin(theta);
  result->w.x = 0;

  result->x.y = 0;
  result->y.y = 1;
  result->z.y = 0;
  result->w.y = 0;

  result->x.z = -sin(theta);
  result->y.z = 0;
  result->z.z = cos(theta);
  result->w.z = 0;

  result->x.w = 0;
  result->y.w = 0;
  result->z.w = 0;
  result->w.w = 1;

  return * result;
}
mat4 mat4_rotate_z(float theta)
{
  mat4* result = (mat4*)malloc(sizeof(mat4));
  result->x.x = cos(theta);
  result->y.x = -sin(theta);
  result->z.x = 0;
  result->w.x = 0;

  result->x.y = sin(theta);
  result->y.y = cos(theta);
  result->z.y = 0;
  result->w.y = 0;

  result->x.z = 0;
  result->y.z = 0;
  result->z.z = 1;
  result->w.z = 0;

  result->x.w = 0;
  result->y.w = 0;
  result->z.w = 0;
  result->w.w = 1;

  return * result;
}
