#include "help.h"
#include "ui_help.h"
#include "boton.h"

#include <QPixmap>
#include <QHBoxLayout>
#include <QBitmap>

help::help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::help)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);      // Quitar el marco con los botones

    this->setStyleSheet("help {background-image: url(://IMG/Fondos/fondo_help.png);}");          // mostrar fondo
    QPixmap Mask("://IMG/Fondos/fondo_help.png");                   // Mascara para mostrar esquinas transparentes
    this->setMask(Mask.mask());

    setFixedHeight(637);                                                                // Tamanho de la ventana
    setFixedWidth(1033);

    QPixmap up("://IMG/Botones/top10_ok_up.png");                                     // Creando el boton del ok
    QPixmap down("://IMG/Botones/top10_ok_down.png");

    Boton* ok = new Boton(up,down,84,39);

    ui->verticalLayout->addStretch();                                                  // Espaciador para que el boton quede en la posicion vertical correcta

    QHBoxLayout* HLy = new QHBoxLayout();                                               // Layout para centrar el boton
    HLy->addStretch();
    HLy->addWidget(ok);
    HLy->addStretch();
    ui->verticalLayout->addLayout(HLy);                                                 // Agregar el layout del boton

    connect(ok,SIGNAL(linkActivated(QString)),this,SLOT(accept()));                     // Conectar el boton con la senhal accept
}

help::~help()
{
    delete ui;
}
