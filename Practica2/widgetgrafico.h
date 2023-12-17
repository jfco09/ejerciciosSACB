#ifndef WIDGETGRAFICO_H
#define WIDGETGRAFICO_H

#include <QWidget>
#include <QPainter>

class WidgetGrafico : public QWidget {
    Q_OBJECT
    QPainter *painter;  // Puntero a objeto que va a dibujar líneas
    QPen *lapiz;  // Puntero a objeto que describe color y grosor de líneas
    int esPrimerPunto;  // Buleano cierto si es el primer punto de una gráfica
    int ejeXCompleto;  // Buleano cierto si la gráfica ya ocupa todo el eje X
    int iPunto;  // Posición X del punto siguiente
    double *valores;  // Valores que se muestran en la gráfica
    int nPuntos;
    int huecoX;  // Gap en el eje X donde no se dibuja la gráfica
    double minY;  // Valor mínimo en el eje Y, que va a corresponder al borde inferior de la ventana
    double escalaY, escalaX;  // Factores de escala para llevar de señal a puntos en pantalla
public:
    explicit WidgetGrafico(QWidget *parent = nullptr);  // Constructor
    void setNPuntos(int nPuntosX);  // Establece el número de puntos a utilizar en eje X
    void setHuecoX(int huecoX);  // Establece gap en eje X donde no se dibuja la gráfica
    void setLapiz(QPen * lapiz);  // Establece objeto que indica color y grosor de líneas
    void setRangoY(double minY, double maxY);    // Establece rango de valores a visualizar
    void otroPunto(double y);  // Añade otro valor a la gráfica
    void repinta();  // Redibuja la gráfica
protected:
    void paintEvent(QPaintEvent *event) override;
signals:

};

#endif // WIDGETGRAFICO_H
