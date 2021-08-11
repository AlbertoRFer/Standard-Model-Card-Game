#include "new_game.h"
#include "ui_new_game.h"
#include "boton.h"


#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QBitmap>

new_game::new_game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_game)
{
    ui->setupUi(this);
    setStyleSheet("new_game {background-image: url(://IMG/Fondos/fondo_newgame.png);}");   // Fondo de la ventana
    this->setWindowFlags(Qt::FramelessWindowHint);      // Quito el borde con los botones

    QPixmap Mask("://IMG/Fondos/fondo_newgame.png");       // Mascara para mostrar esquinas transparentes
    this->setMask(Mask.mask());

    setFixedHeight(188);
    setFixedWidth(458);
    QPixmap up("://IMG/Botones/ng_yes_up.png");                                     // Creando el boton del si
    QPixmap down("://IMG/Botones/ng_yes_down.png");
    Boton* yes = new Boton(up,down,83,46);

    up = QPixmap("://IMG/Botones/ng_no_up.png");                                    // Creando el boton del no
    down = QPixmap("://IMG/Botones/ng_no_down.png");
    Boton* no = new Boton(up,down,83,46);

    QHBoxLayout* Botones = new QHBoxLayout();                                       // Layout para los botones
    Botones->addStretch();
    Botones->addWidget(yes);
    Botones->addWidget(no);
    Botones->addStretch();


    ui->verticalLayout->addStretch();                                               // Layout de la ventana
    ui->verticalLayout->addLayout(Botones);
    ui->verticalLayout->addSpacing(10);

    connect(yes,SIGNAL(linkActivated(QString)),this,SLOT(accept()));                // Conectando los botones con accept() y reject()
    connect(no,SIGNAL(linkActivated(QString)),this,SLOT(reject()));

}

new_game::~new_game()
{
    delete ui;
}
