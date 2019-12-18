//created by Tong
#ifndef LIB3DS_VECTOR_H
#define LIB3DS_VECTOR_H
void vector_make(float c[3], float x, float y, float z) ;
void vector_zero(float c[3]) ;
void vector_copy(float dst[3], float src[3]) ;
void vector_add(float c[3], float a[3], float b[3]) ;
void vector_sub(float c[3], float a[3], float b[3]) ;
void vector_scalar_mul(float c[3], float a[3], float k) ;
void vector_cross(float c[3], float a[3], float b[3]) ;
float vector_dot(float a[3], float b[3]) ;
void vector_length(float c[3]) ;
void vector_normalize(float c[3]) ;
void vector_normal(float n[3], float a[3], float b[3], float c[3]) ;
void vector_transform(float c[3], float m[4][4], float a[3]) ;
void vector_min(float c[3], float a[3]) ;
void vector_max(float c[3], float a[3]) ;
void vector_dump(float c[3]) ;
#endif
