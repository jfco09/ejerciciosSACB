#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Se accede siempre con un puntero
    connect(ui->botonOpera,SIGNAL(released()),this,SLOT(botonOperaClick()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::botonOperaClick(){
    QString texto = ui->editorDato->text();

    double x = texto.toDouble();
    x = x * 2;

    QString resultado = QString::asprintf("Resultado");
}
