#include <stdio.h>
//Declaracion de variables
int m[] = { 15, 13, 2, -6, 17, 4, 1, 6, -9, 8 }; // Matriz con los valores
int nElementos = 10; // Número de elementos en la matriz
int main()
{
    //Declaracion posiciones
    int posMinimo, posMaximo = 0;
    //for que recorre el array
    for(int i = 1; i < nElementos; i++){
        //Compara poscion actual con el candidato
        if(m[i] < m[posMinimo] ){
            posMinimo = i;
        }
        if(m[i] > m[posMaximo] ){
            posMaximo = i;
        }
    }
    return 0;
}
