#include <stdio.h>

int main(){
    //Declaración de variables
    int ordenes[] = { 5, 3, 2, 6, 3, 4, 1, 6, 4, 8 }; // Número de órdenes ejecutadas por cada máquina
    int libres[] = { 1, 1, 0, 0, 0, 1, 0, 0, 1, 1 }; // Buleanos que indican qué máquinas están libres
    int nMaquinas = 10; // Número de máquinas existentes
    //Variables
    int i;
    int primera = 1;
    int posmin = 0;
    int maqlibre = 0;

    //bucle for
    for (i = 0; i < nMaquinas; i++)
    {
        //Ver si la máquina i es libre
        if (libres[i])
        {
            //encuntra la primera maquina libre
            if (primera)
            {
                posmin = i;
                primera = 0;
            }

            //busca minimo
            if (ordenes[i] < ordenes[posmin])
            {
                posmin = i;
            }

            maqlibre++;

        }

    }

    return 0;
}

