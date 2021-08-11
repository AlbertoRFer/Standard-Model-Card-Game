#include "juego_ganado.h"
#include "ui_juego_ganado.h"
#include "boton.h"

#include <QHBoxLayout>
#include <QPixmap>
#include <QBitmap>


juego_ganado::juego_ganado(bool top, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::juego_ganado)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);      // Quitar el marco con los botones
    if (top)
        setStyleSheet("juego_ganado {background-image: url(://IMG/Fondos/ganar_fondo.png);}");          // Si esta en el top10 mostrar este fondo
    else
        setStyleSheet("juego_ganado {background-image: url(://IMG/Fondos/ganar_fondo2.png);}");          // Si no esta en el top10 mostrar este fondo

    QPixmap Mask("://IMG/Fondos/ganar_fondo.png");       // Mascara para mostrar esquinas transparentes
    this->setMask(Mask.mask());

    setFixedHeight(212);
    setFixedWidth(408);
    QPixmap up("://IMG/Botones/top10_ok_up.png");                                     // Creando el boton del ok
    QPixmap down("://IMG/Botones/top10_ok_down.png");

    Boton* ok = new Boton(up,down,84,39);

    ui->verticalLayout->addStretch();

    QHBoxLayout* HLy = new QHBoxLayout();
    HLy->addStretch();
    HLy->addWidget(ok);
    HLy->addStretch();
    ui->verticalLayout->addLayout(HLy);

    connect(ok,SIGNAL(linkActivated(QString)),this,SLOT(accept()));


}

juego_ganado::~juego_ganado()
{
    delete ui;
}
