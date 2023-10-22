#include <math.h>
float modulo(float * vector) {
    return sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
}
void unitario(float * vector, float * uni) {
    float m = modulo(vector);
    uni[0] = vector[0] / m;
    uni[1] = vector[1] / m;
    uni[2] = vector[2] / m;
}
void suma(float * v1, float * v2, float * resultado){
    resultado[0] = v1[0] + v2[0];
    resultado[1] = v1[1] + v2[1];
    resultado[2] = v1[2] + v2[2];
}
void resta(float * v1, float * v2, float * resultado){
    resultado[0] = v1[0] - v2[0];
    resultado[1] = v1[1] - v2[1];
    resultado[2] = v1[2] - v2[2];
}
void multiplica(float * v1, float a, float * resultado){
    resultado[0] = v1[0] * a;
    resultado[1] = v1[1] * a;
    resultado[2] = v1[2] * a;
}
float producto(float * v1, float * v2){
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}
void vectorial(float * v1, float * v2, float * resultado){
    resultado[0] = v1[1] * v2[2] - v1[2] * v2[1];
    resultado[1] = v2[0] * v1[2] - v1[0] * v2[2];
    resultado[2] = v1[0] * v2[1] - v2[0] * v1[1];
}
