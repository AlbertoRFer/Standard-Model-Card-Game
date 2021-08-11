#include "top10.h"
#include "ui_top10.h"
#include "boton.h"

#include <QLabel>
#include <QTableWidgetItem>
#include <QGridLayout>
#include <QTableWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QTime>
#include <QPixmap>
#include <QFont>
#include <QBitmap>

Top10::Top10(Top Lista, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Top10)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);      // Quitar el marco con los botones


    setStyleSheet("Top10 {background-image: url(://IMG/Fondos/fondo_top10.png);}");   // Fondo de la ventana
    QPixmap Mask("://IMG/Fondos/fondo_top10.png");       // Mascara para mostrar esquinas transparentes
    this->setMask(Mask.mask());


    QLabel* l = new QLabel("");                             // Agrego elemento invisible para que se lea bien Top10
    ui->gridLayout->addWidget(l,0,0,1,1);

    setFixedHeight(410);            // Tamanho de la ventana
    setFixedWidth(356);
    QTableWidget* Tabla = new QTableWidget();   // Nueva tabla

    Tabla->setColumnCount(3);                   // Cantidad de columnas
    Tabla->setRowCount(10);                     // Cantidad de filas

    Tabla->setColumnWidth(0,30);                // Ancho de las columnas
    Tabla->setColumnWidth(1,150);
    Tabla->setColumnWidth(2,150);

    Tabla->horizontalHeader()->setVisible(false);   // No mostrar headers
    Tabla->verticalHeader()->setVisible(false);

    Tabla->setEditTriggers(QAbstractItemView::NoEditTriggers);  // No editar la tabla
    Tabla->setStyleSheet("background-color: rgba(255, 255, 255, 128)");     // Fondo se,itransparente de la tabla
    QFont fuente("MV Boli",15);                                 // Fuente para que usen los item de la tabla


    ui->gridLayout->addWidget(Tabla,1,0,10,7);      // Agregar tabla al layout

    QPixmap up("://IMG/Botones/top10_ok_up.png");                                     // Creando el boton del ok
    QPixmap down("://IMG/Botones/top10_ok_down.png");
    Boton* yes = new Boton(up,down,84,39);

    //QPushButton* PB = new QPushButton("Aceptar");   // Boton aceptar
    ui->gridLayout->addWidget(yes,11,3,1,1);         // Agregar boton a la tabla

    for (int i=0;i<10;i++)                          // Llenar las filas
    {

        QTableWidgetItem *newItem = new QTableWidgetItem(QString::number(i+1));     // Posicion en la tabla (i+1)
        newItem->setTextAlignment(Qt::AlignCenter);
        newItem->setFont(fuente);
        Tabla->setItem(i, 0, newItem);

        newItem = new QTableWidgetItem(Lista.Nombre[i]);                            // Iesimo nombre
        newItem->setFont(fuente);
        Tabla->setItem(i, 1, newItem);

        QTime T(Lista.H[i],Lista.M[i],Lista.S[i]);                                  // Iesimo tiempo
        newItem = new QTableWidgetItem(T.toString());
        newItem->setTextAlignment(Qt::AlignCenter);
        newItem->setFont(fuente);
        Tabla->setItem(i, 2, newItem);
    }    
    //connect(PB,SIGNAL(clicked()),this,SLOT(accept()));                              // Conectar boton aceptar con el accept()
    connect(yes,SIGNAL(linkActivated(QString)),this,SLOT(accept()));

}

Top10::~Top10()
{
    delete ui;
}
