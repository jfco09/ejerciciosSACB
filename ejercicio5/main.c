#include <stdio.h>
#include <math.h>
//Declaracion de funciones a usar
//establece la actuacion
void salidaAnalogica(double valor);
//devuelve el valor actual de la entrada si nEntrada = 1
double entradaAnalogica(int nEntrada);
//MS autoincrementado por el micro, cada 1ms
unsigned int MS ;

//Funcion de autoajuste del PID
void autoajustePID(float actuacion, float  * Kp, float * Ki, float *Kd){
    //Declaracion de variables a usar
    int finalizar = 1, nPeriodos = 0;
    double P[5], A[5], mediaA= 0,mediaP = 0;
    float pi = 3.141592;
    float Ku = 0;

    //Suponiendo empezamos con 0V activamos salida a actuacion (5V)
    salidaAnalogica(actuacion);
    //Esperamos a que llegue a 0.5V
    while(entradaAnalogica(1) < 0.5);
    //Actuamos con -actuacion (-5V) y esperamos a que pase por 0V
    salidaAnalogica(-actuacion);
    while(entradaAnalogica(1) > 0);

    //bucle que espera la estabilizacion de la señal
    while(finalizar){
        //iniciamos el contador del micro y el contador de periodos
        MS = 0;
        nPeriodos++;
        //activamos salida a actuacion (5V)
        salidaAnalogica(actuacion);

        //busca el minimo
        double minimo = 0, y;
        do {
            y = entradaAnalogica(1);
            if(y < minimo){
                minimo = y;
            }
        } while (y < 0);

        salidaAnalogica(-actuacion);
        //busca el maximo
        double maximo = 0;
        do {
            y = entradaAnalogica(1);
            if(y > maximo){
                minimo = y;
            }
        } while (y > 0);

        //Desplaza los valores almacenados en A y en P
        for (int i = 0; i < 4; ++i) {
            A[i] = A[i+1];
            P[i] = P[i+1];
        }
        A[4] = maximo - minimo;
        P[4] = MS / 1000.0;

        //cada 5 periodos calcula media de Amplitud y media de P
        if(nPeriodos == 5){

            mediaA = 0;
            mediaP = 0;
            for (int i = 0; i < 5; ++i) {
                mediaA += A[i];
                mediaP += P[i];
            }
            mediaA /= 5;
            mediaP /= 5;
            //suponemos que ha finalizado
            finalizar = 0;
            // si algun valor no cumple con el rango continuamos buscando
            for (int i = 0; i < 5; ++i) {
                if(fabs(A[i] - mediaA) > 0.02 * mediaA || fabs(P[i] - mediaP) > 0.02 * mediaP  ){
                    finalizar = 1;
                }
            }
            //reiniciamos el nº de periodos a 0
            nPeriodos = 0;
        }

    }
    //cuando señal sea estable (finalizar = 0) calculamos los parametros del rele
    Ku = (4 * actuacion) / (pi * mediaA);
    *Kp = 0.6 * Ku;
    *Ki = 1.2 * Ku / mediaP;
    *Kd = 0.075 * Ku;

}

int main()
{
    float Kp,Ki,Kd;
    autoajustePID(5,& Kp,& Ki,& Kd);

    return 0;
}
