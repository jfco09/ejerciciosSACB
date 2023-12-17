#include <stdio.h>
//Declaracion de la matriz
int m[] = { 5, 3, 2, 6, 3, 4, 1, 6, 4, 8 };
int main() {
    //Se supone que el primer elemento es el minimo
    int minimo = m[0];
    //Bucle que recorre el array m
    for (int i = 0; i < 10; i++)
        if (m[i] < minimo)
            minimo = m[i];
    return minimo;
}
