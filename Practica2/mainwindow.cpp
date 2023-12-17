#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datos.h"

#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widgetResp->setNPuntos(1000);
    ui->widgetResp->setHuecoX(10);
    QPen * p = new QPen(QColor(0, 255, 0));
    ui->widgetResp->setLapiz( p);
    ui->widgetResp->setRangoY(0,1);
    ui->widgetResp->otroPunto(0.5);
    int filas = 60001;
    int columnas= 6;
    int minimos[6];
    int maximos[6];

    for (int j = 0; j < columnas; ++j) {
        int minimo = datos[0][j];
        int maximo = datos[0][j];

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

    for (int i = 0; i < 60000; ++i) {
        ui->widgetResp->otroPunto(datos[i][1]);

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

