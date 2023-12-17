#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datos.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //Obtencion maximos y minimos de la señal
    int filas = 60001;
    int columnas = 6;

    for (int j = 0; j < columnas; ++j) {
        double minimo = datos[0][j];
        double maximo = datos[0][j];

        for (int i = 1; i < filas; ++i) {
            if (datos[i][j] < minimo) {
                minimo = datos[i][j];
            }

            if (datos[i][j] > maximo) {
                maximo = datos[i][j];
            }
        }
        minimos[j] = minimo;
        maximos[j] = maximo;
    }



    ui->setupUi(this);

    //Inicialización de las graficas
    int N = 1000;
    int hueco = 1;

    ui->widgetResp->setNPuntos(N); //Establece el numero de puntos total
    ui->widgetResp->setHuecoX(hueco); //Hueco en X al dibujar
    QPen * p = new QPen(QColor(0, 255, 0),1.5); // Color y grosor de la gráfica
    ui->widgetResp->setLapiz( p); //Pasarle el objeto creado al constructor
    ui->widgetResp->setRangoY(minimos[1],maximos[1]); //Rangos en Y calculados previamente

    ui->widgetPPG->setNPuntos(N);
    ui->widgetPPG->setHuecoX(hueco);
    QPen * p1 = new QPen(QColor(0, 255, 255),1.5);
    ui->widgetPPG->setLapiz( p1);
    ui->widgetPPG->setRangoY(minimos[2],maximos[2]);

    ui->widgetPPM_1->setNPuntos(N);
    ui->widgetPPM_1->setHuecoX(hueco);
    QPen * p2 = new QPen(QColor(255, 0, 0),1.5);
    ui->widgetPPM_1->setLapiz( p2);
    ui->widgetPPM_1->setRangoY(minimos[3],maximos[3]);

    ui->widgetPPM_2->setNPuntos(N);
    ui->widgetPPM_2->setHuecoX(hueco);
    QPen * p3 = new QPen(QColor(255, 0, 0),1.5);
    ui->widgetPPM_2->setLapiz( p3);
    ui->widgetPPM_2->setRangoY(minimos[4],maximos[4]);

    ui->widgetPPM_3->setNPuntos(N);
    ui->widgetPPM_3->setHuecoX(hueco);
    QPen * p4 = new QPen(QColor(255, 0, 0),1.5);
    ui->widgetPPM_3->setLapiz( p4);
    ui->widgetPPM_3->setRangoY(minimos[5],maximos[5]);



    //Simular la obtención de la señal de 125Hz
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(actualizarDatos()));
    timer->start(8); // 1/125Hz = 8ms

}

void MainWindow::actualizarDatos()
{
    //Valores para la deteccion de picos resp
    vpasado_resp = datos[indice - 2 ][1];
    vact_resp =   datos[indice - 1 ][1] ;
    vfuturo_resp=   datos[indice][1];
    umbral_resp= maximos[1] * 0.8 ;

    if(vact_resp < maximos[1] * 0.2 && vact_resp > vfuturo_resp){
        subiendo = 1;
    }
    if (vact_resp > maximos[1] * 0.5 && subiendo) {
        tresp[0] = tresp[1];
        tresp[1] =  datos[indice - 1][0] ;
        picos_resp ++;
        subiendo = 0;
    }

    /*

    //Encontrar picos respiratorios
    if (indice > 5  ) {
        if (vact_resp >= vpasado_resp && vact_resp > vfuturo_resp  &&  vact_resp > umbral_resp) {
            tresp[0] = tresp[1];
            tresp[1] =  datos[indice - 1][0] ;
            picos_resp ++;
        }

    }
    */

    //Actulizar valores cada 0.8s los valores de resp
    if (indice % 100 == 0 && picos_resp > 1){
        resps = 60 / (tresp[1] - tresp[0])  ;
        //Evita primer caso
        if (max_resp == 0 || min_resp ==0){
            max_resp = resps;
            min_resp = resps;

        }else{
            //Actualiza max y min de ppms
            if (resps > max_resp){
                max_resp = resps;
            }
            if (resps < min_resp){
                min_resp = resps;
            }

        }
        //Actualiza resp UI
        ui->lb_resp->setText(QString::number(resps, 'f', 0));
        ui->lb_max_resp->setText(QString::number(max_resp, 'f', 0));
        ui->lb_min_resp->setText(QString::number(min_resp, 'f', 0));
    }


    //Valores para la deteccion de picos ppm
    vpasado_ppm = datos[indice - 2 ][5];
    vact_ppm =   datos[indice -1][5] ;
    vfuturo_ppm =   datos[indice][5];
    umbral_ppm = maximos[5] * 0.9 ;

    //Encontrar picos ppm
    if (indice > 5  ) {
        if (vact_ppm >= vpasado_ppm && vact_ppm > vfuturo_ppm &&  vact_ppm > umbral_ppm) {
            tppm[0] = tppm[1];
            tppm[1] =  datos[indice - 1][0] ;
            picos_ppm ++;

        }

    }

    //Actulizar valores cada 0.4s los valores de ppms
    if (indice % 50 == 0 && picos_ppm > 1){
        ppm = 60 / (tppm[1] - tppm[0])  ;
        //Evita primer caso
        if (max_ppm == 0 || min_ppm ==0){
            max_ppm = ppm;
            min_ppm = ppm;

        }else{
            //Actualiza max y min de ppms
            if (ppm > max_ppm){
                max_ppm = ppm;
            }
            if (ppm < min_ppm){
                min_ppm = ppm;
            }

        }
        //Actualiza ppm UI
        ui->lb_ppm->setText(QString::number(ppm, 'f', 0));
        ui->lb_max_ppm->setText(QString::number(max_ppm, 'f', 0));
        ui->lb_min_ppm->setText(QString::number(min_ppm, 'f', 0));
    }

    //Dibujar graficas
    ui->widgetResp->otroPunto(datos[indice][1]);
    ui->widgetPPG->otroPunto(datos[indice][2]);
    ui->widgetPPM_1->otroPunto(datos[indice][3]);
    ui->widgetPPM_2->otroPunto(datos[indice][4]);
    ui->widgetPPM_3->otroPunto(datos[indice][5]);


    //incrementar indice
    ++indice;
    if (indice >= 60000) {
        // Restablecer el índice al llegar al final de los datos
        indice = 0;
        picos_ppm = 0;
        picos_resp = 0;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
