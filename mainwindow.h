#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QPushButton>
#include <QSignalMapper>
#include <QLabel>
#include <QGroupBox>
#include <QString>

#include "FlipWidget.h"
#include "digitalclock.h"
#include "Tipos_datos.h"
#include "boton.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QSignalMapper* mapa;            //Para mapear las señales segun indice de la lista
    QList<QFlipWidget* > ListaFlip;  //Lista de imagenes

    QLabel* lbl_name;               //Mostrar tiempo transcurrido

    int volteado;                   //Cantidad de cartas volteadas
    int i_ant;                      //indice de la primera carta volteada
    int i_act;                      //indice de la segunda carta volteada

    int p_elim;                     //cantidad de parejas eliminadas
    DigitalClock* D_Clock_Timer;    //Widget para mostrar el tiempo de juego

    bool Game_paused;               //Indica si el juego esta en pausa
    Top ListaTop;                   //Listado con los mejores jugadores
    bool Jugando;                   //Indica si se esta jugando

    QString Nombre;                 //Nombre del Jugador
    QList<QLabel* > Top3;           //Lista de labels del Top3

    Boton* B2;                      //Boton de pause
private slots:

    void cargar_info();                 // Se cargan los datos del Top10 y el nombre del ultimo jugador
    void guardar_info();                // Guarda los datos en el archivo, lo mantiene actualizado

    void start_game();                  // Se reparten las cartas y se inicia un nuevo juego
    void setCardImage(int i, int N);    // Se asignan las imagenes a las cartas

    void imagen_press(int i);           // Controla lo que pasa cuando se presiona una carta
    void comprobar_igual();             // Comprueba si dos cartas son iguales
    void espera_voltear();              // Se voltean las dos cartas si no son iguales
    void espera_desaparecer();          // Se desaparecen las dos cartas si son iguales
    void game_over();                   // Muestra pantalla de fin de juego

    void pause_unpause();               // Controla las pausas y el boton correspondiente

    void mostrar_top();                 // Muestra el top10

    void mostrar_ayuda();               // Muestra la ayuda

    void cambiar_nombre();              // Controla el cambio del nombre y actualiza el label correspondiente

    void actualizar_top3();             // Actualiza el top3


    void prueba();  //Debug

};

#endif // MAINWINDOW_H
