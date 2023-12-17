#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void actualizarDatos();
private:
    Ui::MainWindow *ui;
    int indice = 0;
    double minimos[6];
    double maximos[6];

    int picos_ppm = 0;
    double ppm = 0.0;
    double tppm[2] = {0.0, 0.0};
    double umbral_ppm = 0.0;
    double vact_ppm,vpasado_ppm,vfuturo_ppm = 0.0;
    double max_ppm, min_ppm = 0.0;

    int picos_resp = 0;
    double resps = 0.0;
    double tresp[2] = {0.0, 0.0};
    double umbral_resp = 0.0;
    double vact_resp,vpasado_resp,vfuturo_resp = 0.0;
    double max_resp, min_resp = 0.0;
    int subiendo = 0;
};
#endif // MAINWINDOW_H
