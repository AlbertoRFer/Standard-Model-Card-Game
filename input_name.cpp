#include "input_name.h"
#include "ui_input_name.h"
#include "boton.h"

#include <QPixmap>
#include <QBitmap>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFont>

Input_name::Input_name(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Input_name)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);      // Quitar el marco con los botones
    setStyleSheet("Input_name {background-image: url(://IMG/Fondos/name_fondo.png);}");   // Fondo de la ventana

    QPixmap Mask("://IMG/Fondos/name_fondo.png");       // Mascara para mostrar esquinas transparentes
    this->setMask(Mask.mask());

    setFixedHeight(158);
    setFixedWidth(258);

    //QLabel* l = new QLabel("");
    //ui->verticalLayout->addWidget(l);
    ui->verticalLayout->addSpacing(50);

    QHBoxLayout* hLy = new QHBoxLayout();                                   // Layout horizontal para el edit
    hLy->addStretch();                                                      // Spacers para centrar el Edit

    Edit = new QLineEdit();
    Edit->setInputMask("Aaaaaaaaaaaaa");                                    // Solo se pueden escribir esta cantidad de letras
    Edit->setStyleSheet("background-color: rgba(255, 255, 255, 32)");       // Fondo semitransparente
    QFont f("MV Boli",14);                                                  // Fuente del edit
    Edit->setFont(f);
    hLy->addWidget(Edit);                                                   // Agrego el edit al layout
    connect(Edit,SIGNAL(editingFinished()),this,SLOT(accept()));            // Si se toca enter se presiona el aceptar
    hLy->addStretch();

    ui->verticalLayout->addLayout(hLy);                                     // Se agrega el layout del edit al de la ventana

    hLy = new QHBoxLayout();                                                // Layout de los botones
    hLy->addStretch();                                                      // Spacers para centrar los botones

    QPixmap up("://IMG/Botones/top10_ok_up.png");                                     // Creando el boton del ok
    QPixmap down("://IMG/Botones/top10_ok_down.png");
    Boton* ok = new Boton(up,down,84,39);
    hLy->addWidget(ok);

    up = QPixmap("://IMG/Botones/name_cancel_up.png");                                // Creando el boton del cancel
    down = QPixmap("://IMG/Botones/name_cancel_down.png");
    Boton* cancel = new Boton(up,down,98,39);
    hLy->addWidget(cancel);
    hLy->addStretch();

    ui->verticalLayout->addLayout(hLy);                                                 // Agregando layout de los botones al de la ventana

    connect(ok,SIGNAL(linkActivated(QString)),this,SLOT(accept()));                     // Conectando los botones a las senhales accept y reject
    connect(cancel,SIGNAL(linkActivated(QString)),this,SLOT(reject()));

}

Input_name::~Input_name()
{
    delete ui;
}
QString Input_name::nombre()
{
    return Edit->text();                        // Devolver el nombre
}

