#include <iostream>

using namespace std;

int datoIntroducido();
double recogeDato();
void enviaPaquete(void *p, int n);
void creaTemporizador(int periodo);
void esperaTemporizador();
int paqueteRecibido(void);
int recibePaquete(void * p);
double entrada();
void salida(double salida);
void mainS1()

{
    creaTemporizador(1000);
    while(1){
        double consigna = 0.0;
        if (datoIntroducido()) {
            double consigna = recogeDato();
        }
        enviaPaquete(& consigna, sizeof(consigna));
        esperaTemporizador();
    }
}

void mainS2()
{
    double uk = 0.0, uk1 = 0.0, ek = 0.0, ek1 = 0.0;
    double T = 0.1, Kp = 0.1, Ki = 0.1 ;
    double a = Kp + Ki * T;
    double c;

    while(1){
        if (paqueteRecibido()) {
            recibePaquete( &c);

        }
        ek = c - entrada();
        uk = uk1 + a  * ek - Kp * ek1 ;
        salida(uk);
        uk1 = uk;
        ek1 = ek;
    }




}
