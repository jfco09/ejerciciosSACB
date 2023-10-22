#include <stdio.h>
void arrancaTemporizador(int, int);
void esperaTemporizador();
float mideSenal();
void borraPantalla();
void dibujaLinea(int x1, int y1, int x2, int y2);

int main()
{
    //Inicializar variables
    float v_act = 0;
    float v_filtrado = 0;
    float u[5] = {0, 0, 0, 0, 0}, y[5] = {0, 0, 0, 0, 0};
    int n=0;
    //inicializa el array medidas a 4000
    float medidas[4000];

    for (int i = 0; i < 4000; ++i) {
        medidas[i] = 0;
    }

    //inicia el temporizador para que salte cada 1ms
    arrancaTemporizador(0,1000000);
    while(1){
        //espera finalizacion temporizador
        esperaTemporizador();
        n++;
        //almacena en medida el valor actual de la senal
        v_act = mideSenal();
        //aplica el filtro
        v_filtrado = 2.9745 * y[4] - 3.8060 * y[3] + 2.5453 * y[2] - 0.8811 * y[1] + 0.1254 * y[0]
                 + 0.0013 * v_act + 0.0064 * u[4] + 0.0128 * u[3] + 0.0128 * u[2]
                 + 0.0064 * u[1] + 0.0013 * u[0];
        //desplaza los valores de las señales filtradas y las no filtradas
        for (int i = 0; i < 3; --i) {
            y[i] = y[i+1];
            u[i] = u[i+1];
        }
        //actuliza el valor
        y[4] = v_filtrado;
        u[4] = v_act;
        //desplaza las medidas
        for (int i = 0; i < 3999; ++i) {
            medidas[i] = medidas[i+1];
        }
        //actualiza en ultimo valor
        medidas[3999] = v_filtrado;
        //espera a muestrear 2000 muestras (2s)
        if(n  == 2000){
            //funcion que elimina toda la pantalla
            borraPantalla();
            //recorre todas las medidas y las dibuja
            for (int i = 0; i < 3999; ++i) {
                //dibujaLinea(i*1023/3999, (717- 767/2)/3 * medidas[i] +767/2,(i+1)*1023/3999,(717- 767/2)/3 * medidas[i+1] +767/2);
                dibujaLinea(i*1023/3999, (717+50)/6*(medidas[i]+3) +50,(i+1)*1023/3999,(717+50)/6*(medidas[i+1]+3) +50);
            }
            n = 0;
        }
        //vuelve a arrancar el temporizador para esperar otra obtencion
        arrancaTemporizador(0,1000000);

    }
}
