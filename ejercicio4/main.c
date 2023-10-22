#include <stdio.h>
#include <vectores.c>

int main()
{
    float p1[] = {5.07, 3.28, 2.16};
    float p2[] = {10.53, 12.19, 17.72};
    float p3[] = {21.01, 15.63, 6.97};
    float p4[] = {-3.15, 4.96, 0.32};

    int nPuntos = 20;
    float puntos[20 * 3];
    float direccion[3];
    float v13[3], v12[3], v14[3], v123[3], v124[3], u123[3], u124[3], b[3], bu[3], desplazamiento[3];

    resta(p3, p1, v13);
    resta(p2, p1, v12);
    resta(p4, p1, v14);

    vectorial(v13, v12, v123);
    vectorial(v12, v14, v124);

    unitario(v123, u123);
    unitario(v124, u124);

    suma(u123, u124, b);
    unitario(b, bu);

    multiplica(bu, 0.2, desplazamiento);

    float d12 = modulo(v12);
    float d = d12 / 19;

    float u12[3], vd[3];
    unitario(v12, u12);
    multiplica(u12, d, vd);

    suma(p1, desplazamiento, puntos);
    for(int i = 1; i < nPuntos; i++)
        suma(puntos + (i-1) * 3, vd, puntos + i * 3);

    multiplica(bu, -1, direccion);

    return 0;
}
