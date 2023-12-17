#include <stdio.h>

int main()
{
    int m[] = { 15, 13, 2, -6, 17, 4, 1, 6, -9, 8 }; // Matriz con los valores
    int nElementos = 10; // Número de elementos en la matriz
    //Bucle for recorre las posiciones donde se pone el minimo nElementos-1 porque ultima fila no es necesario colocar el minimo local
    for(int j = 0; j < nElementos - 1; j++ ){
        //Declaracion de variables auxiliares
        int minimo =  m[j];
        int posmin = j;
        //Bucle for que recorre las matrices a partir del minimo a obtener
        for(int i = j; i < nElementos; i++){
            if (m[i] < minimo){
                minimo = m[i];
                posmin = i;
            }
        }
        //Realiza el intercambio de valores
        m[posmin] = m[j];
        m[j] = minimo;
    }
    return 0;
}
