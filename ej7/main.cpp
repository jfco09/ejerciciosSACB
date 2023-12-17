#include <iostream>

using namespace std;

int datoIntroducido();
double recogeDato();
void enviaPaquete(void *p, int n);
void creaTemporizador(int periodo);
void esperaTemporizador();
int main()
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
    return 0;
}
