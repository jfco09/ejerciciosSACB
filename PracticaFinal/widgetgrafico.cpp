#include "widgetgrafico.h"
#include <QPainter>
#include <cmath>


WidgetGrafico::WidgetGrafico(QWidget *parent) : QWidget(parent){
    // Constructor. Se indica por parámetro un puntero al widget donde se muestra este
    // widget gráfico
    
    ejeXCompleto = 0;  // Inicialmente no se completó el dibujado de la gráfica a lo largo del eje X
    iPunto = 0;  // Número de punto a dibujar
    esPrimerPunto = 1;  // Buleano que indica que se va a dibujar el primer punto
    huecoX = 0;  // Inicialmente no se utiliza ningún gap
}

void WidgetGrafico::repinta() {  // Redibuja la gráfica en pantalla
    repaint();  // Llamada a este método recibido mediante herencia desde la clase QWidget, para
                // provocar el borrado del widget gráfico y la generación de un evento que lo va
                // a tratar el método paintEvent definido a continuación
}

void WidgetGrafico::paintEvent(QPaintEvent *) {
    // Se ejecuta automáticamente cada vez que se llama al método repaint()
    
    QPainter pintor(this);
    // Crea un objeto de la clase QPainter asociado a este widget gráfico, con el que dibujar líneas
    
    pintor.setRenderHint(QPainter::Antialiasing);
    // Activa antialiasing para que las líneas tengan bordes suaves y no con saltos
    
    pintor.setPen(*lapiz);
    // Establece el color de dibujado y el grosor
    
    double x, y, x0 = 0, y0 = 0;
    
    if (ejeXCompleto) {  // Si se completó el dibujado de la gráfica en todo el eje X ...
        
        for (int i = 0; i <= iPunto; i ++) {
            // Desde el primer punto hasta el punto iPunto ...
            
            x = i * escalaX;  // Obtiene su coordenada X en pantalla
            
            y = height() - (valores[i] - minY) * escalaY;
            // Obtiene su coordenada Y en pantalla
            // height() es el alto de la ventana, se utiliza aquí debido a que el eje Y comienza en
            // la esquina superior izquierda y crece positivo hacia abajo.
            // valores[i] es el valor de la señal para el punto i-ésimo.
            // minY es el mínimo de todos esos valores.
            // escalaY es el factor de escala que hay que aplicar para pasar de valores de la señal a
            // coordenadas en pantalla en el eje Y.
            
            if (i > 0)  // Si no es el primer punto ...
                pintor.drawLine(x0, y0, x, y);  // Dibuja una línea desde el punto anterior (x0,y0) a este (x,y)
            x0 = x;  // Guarda el punto actual en el anterior
            y0 = y;
        }
        
        int iInicial = iPunto + huecoX + 1;  // Se salta tantos puntos como el gap definido
        
        // Dibuja el resto de la señal hasta el final del eje X
        for (int i = iInicial; i < nPuntos; i++) {
            x = i * escalaX;
            y = height() - (valores[i] - minY) * escalaY;
            if (i > iInicial)
                pintor.drawLine(x0, y0, x, y);
            x0 = x;
            y0 = y;
        }
        
    } else {  // Aún no se completó el dibujado de toda la señal a lo largo del eje X
        
        // Conecta con líneas todos los puntos, sin gap
        for (int i = 0; i <= iPunto; i ++) {
            x = i * escalaX;
            y = height() - (valores[i] - minY) * escalaY;
            if (i > 0)
                pintor.drawLine(x0, y0, x, y);
            x0 = x;
            y0 = y;
        }
    }
}


void WidgetGrafico::setLapiz(QPen *lapiz) {
    // Se pasa por parámetro un puntero a un objeto de la clase QPen donde se indica el
    // color y grosor de las líneas con las que se dibuja una gráfica
    
    this->lapiz = lapiz;  // Copia el puntero en otro puntero en la clase
}


void WidgetGrafico::setNPuntos(int nPuntos){
    // Establece cuántos puntos se van a representar simultáneamente como máximo en pantalla, tienen que
    // ocupar todo el eje horizontal
    
    this->nPuntos = nPuntos;  // Guarda la cantidad de puntos a utilizar
    valores = new double[nPuntos];  // Crea una matriz de números reales para guardar los valores de las señales
    escalaX = (width() - 1.0)/ (nPuntos - 1);  // Escala a aplicar en el eje X, donde width() es el ancho de la ventana
}


void WidgetGrafico::setHuecoX(int huecoX) {
    // Para indicar el número de puntos de la gráfica que no se van a dibujar en el gap móvil
    
    this->huecoX = huecoX;  // Guarda en el objeto ese dato
}


void WidgetGrafico::setRangoY(double minY, double maxY) {
    // Establece el rango utilizado en el eje Y para la señal que se va a representar en la gráfica, de forma
    // que el valor minY se representa en el borde inferior  de la ventana y maxY en el superior
    
    this->minY= minY;  // Guarda el mínimo
    
    escalaY = (height() - 1) / (maxY - minY);
    // Factor de escala para pasar del valor de la señal a coordenada Y en la ventana
}


void WidgetGrafico::otroPunto(double y) {
    // Añade un nuevo valor de señal a la gráfica
    
    if (esPrimerPunto) {  // Si es el primero ...
        valores[0] = y;  // Lo guarda
        esPrimerPunto = 0;  // Indica que ya se guardó el primero
    } else {  // si no ...
        iPunto ++;  // Indica que hay un punto más
        if (iPunto == nPuntos) {  // Si se alcanzó el último punto que corresponde al borde derecho de la ventana ...
            iPunto = 0;  // Vuelve al borde izquierdo
            ejeXCompleto = 1;  // Indica que ya se completó el eje X
        }
        valores[iPunto] = y;  // Guarda el valor
        repaint();  // Provoca el borrado y redibujado de la gráfica, que se realiza en el método paintEvent()
    }
}


