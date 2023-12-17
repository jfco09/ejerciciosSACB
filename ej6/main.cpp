#include <stdio.h>

//Clase temporizador
class Temporizador
{
public:
    Temporizador(int periodo) {
        void espera();
    }
};
//Declaración de variables
double entradaAnalogica();
void salidaAnalogica(double valor);
int interruptor();
void dibujaPunto(int x, int y, int color);
void borra();
int main()
{
    Temporizador t(100);

    double y = 0.0; //Salida del proceso
    double r; // Consigna del proceso
    double u[2] = {0.0, 0.0}; //Matriz actuaciones proceso
    double e[2] = {0.0, 0.0}; //Matriz errores proceso

    float a, Kp, T, Ti; //Variables controlador
    T = 0.1;
    Kp = 0.1;
    Ti = 10;
    a = Kp * (1 + T / Ti);

    int xPunto = 0;

    double my[480]; //Salida del proceso
    double mr[480]; // Consigna del proceso

    while(1){
        r = interruptor(); //Actualizar valor actual de la consigna
        y = entradaAnalogica(); //Actualizar valor actual salida

        u[1] = u[0]; //Actualizar valor anterior actuacion

        e[1] = e[0]; //Actualizar valor anterior error

        e[0] = interruptor() - y; //Calcular valor actual error

        u[0] = u[1] * a * e[0] - Kp * e[1]; //Calcular valor actual actuacion

        salidaAnalogica(u[0]);


        if (xPunto < 480){
            dibujaPunto(xPunto, 160 * (1.5 - r), 0x7FFFFF); // dibujar
            dibujaPunto(xPunto, 160 * (1.5 - y), 0xFFFF00);

            mr[xPunto] = r;
            my[xPunto] = y;

            xPunto ++;

        } else{
            void borra();
            for (int i = 0; i < 479; ++i) {
                mr[i] = mr[i+1];
                my[i] = my[i+1];

            }
            mr[479] = r;
            my[479] = y;
            for (int x = 0; x < x; ++x) {
                dibujaPunto(x, 160* (1.5 - mr[x]), 0x7FFFFF);

            }
        }

    }
    return 0;
}
