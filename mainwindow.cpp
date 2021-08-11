#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QTime>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QErrorMessage>
#include <QFileInfo>
#include <QFont>

#include "FlipWidget.h"
#include "digitalclock.h"
#include "top10.h"
#include "input_name.h"
#include "new_game.h"
#include "juego_ganado.h"
#include "help.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedHeight(695);                  // Tamanho de la ventana
    this->setFixedWidth(895);

    setStyleSheet("MainWindow {background-image: url(://IMG/Fondos/back.jpg);}");   // Fondo de la ventana

    volteado=0;                         // Inicializacion de algunas de las variables
    p_elim=0;
    Game_paused=false;
    Jugando=false;

    cargar_info();                      // Se cargan la informacion del top10 y el nombre del ultimo jugador

    //------------------------------------------- Creacion de la interfaz -------------------------------------------------

    QGroupBox* GBIZ = new QGroupBox();      // Agrupa las cartas
    QGroupBox* GBDER = new QGroupBox();     // Agrupa las informaciones

    GBDER->setObjectName(QString("Box"));
    GBDER->setStyleSheet("QWidget#Box {background-color: rgba(255, 255, 255, 64);}");

    ui->gridLayout->addWidget(GBIZ,0,0,1,3);    // Se agregan al grid
    ui->gridLayout->addWidget(GBDER,0,3,1,1);

    //----------------------------------- Panel izquierdo (cartas) ----------------------------------

    QGridLayout* gLy_Cards = new QGridLayout(GBIZ); // Grid para agrupar las cartas

    mapa = new QSignalMapper(this);                 // Para saber de que carta viene la senhal clicked()

    QPixmap px;                                     // Fondo de las cartas
    px.load(QString("://IMG/Particulas/Fondo3.png"));

    for (int i=0;i<6;i++)                           // Doble for para la cuadricula de 6x6
    {
        for (int j=0;j<6;j++)
        {
            QGroupBox* GB = new QGroupBox();        // Groupbox para cada una de las cartas (solo estetica)

            QFlipWidget* b = new QFlipWidget(QRectF(0,0,100,100),px,px,false,GB);   // Se crea un FlipWidget en el Groupbox anterior
            b->setGeometry(QRect(5,7,90,90));       // Se establece el tamanho

            ListaFlip.append(b);                    // Se agrega a la lista de cartas
            gLy_Cards->addWidget(GB,i,j,1,1);       // Se agrega el groupbox al grid de las cartas

            connect(ListaFlip[i*6+j],SIGNAL(clicked()),mapa,SLOT(map()));     // Conexion de los FlipWidget
            mapa->setMapping(ListaFlip[i*6+j],i*6+j);                         // Se establece el mapa
            ListaFlip[i*6+j]->setVisible(false);                              // Se ocultan las cartas hasta que se le ponga la imagen de su particula
        }
    }

    connect(mapa,SIGNAL(mapped(int)),this,SLOT(imagen_press(int)));     // Conectando señales al mapa

    //--------------------------------- Panel derecho (botones e informacion) -------------------------------

    QVBoxLayout* hbLy_info = new QVBoxLayout(GBDER);                    // Se crea el layout del panel de la derecha

    //--------------------- Mostrar y cambiar nombre ---------------
    QString QS("<p>Hi <b><i><u>" + Nombre + "</u></i></b><br> Click <a href=#>here</a> if this <br> is not your name</p>");
    lbl_name = new QLabel(QS);
    lbl_name->setFixedHeight(95);
    lbl_name->setWordWrap(true);
    lbl_name->setAlignment(Qt::AlignCenter);
    QFont fuente("MV Boli",15);
    lbl_name->setFont(fuente);
    lbl_name->setText(QS);

    connect(lbl_name,SIGNAL(linkActivated(QString)),this,SLOT(cambiar_nombre()));       // Se conecta el link con el metodo de cambiar nombre
    hbLy_info->addWidget(lbl_name);

    //--------------------- Boton New Game ------------------------

    QGroupBox* GB_B = new QGroupBox();
    hbLy_info->addWidget(GB_B);

    QVBoxLayout* BotLy = new QVBoxLayout(GB_B);

    //QPushButton* B1 = new QPushButton("Nuevo Juego");
    QPixmap up("://IMG/Botones/new_game_up.png");
    QPixmap down("://IMG/Botones/new_game_down.png");
    Boton* B1 = new Boton(up,down,181,56);
    BotLy->addWidget(B1);
    //connect(B1,SIGNAL(clicked()),this,SLOT(start_game()));                              // Se conecta el boton con start_game()
    connect(B1,SIGNAL(linkActivated(QString)),this,SLOT(start_game()));

    //--------------------- Boton Pause ------------------------

    //PB_pause = new QPushButton("Pause");

    up = QPixmap("://IMG/Botones/pause_up.png");
    down = QPixmap("://IMG/Botones/pause_down.png");
    B2 = new Boton(up,down,181,56);
    //connect(PB_pause,SIGNAL(clicked()),this,SLOT(pause_unpause()));
    connect(B2,SIGNAL(linkActivated(QString)),this,SLOT(pause_unpause()));                         // Se conecta el boton con pause_unpause()
    //connect(B2,SIGNAL(linkActivated(QString)),this,SLOT(game_over()));         // Debug
    BotLy->addWidget(B2);

    //--------------------- Boton Top Ten ------------------------

    up = QPixmap("://IMG/Botones/top_ten_up.png");
    down = QPixmap("://IMG/Botones/top_ten_down.png");
    Boton* B3 = new Boton(up,down,181,56);
    //QPushButton* B3 = new QPushButton("Top Ten");
    connect(B3,SIGNAL(linkActivated(QString)),this,SLOT(mostrar_top()));                             // Se conecta el boton con mostrar_top()
    BotLy->addWidget(B3);

    //--------------------- Boton Ayuda ------------------------

    up = QPixmap("://IMG/Botones/help_up.png");
    down = QPixmap("://IMG/Botones/help_down.png");
    Boton* B4 = new Boton(up,down,181,56);
    //QPushButton* B3 = new QPushButton("Top Ten");
    connect(B4,SIGNAL(linkActivated(QString)),this,SLOT(mostrar_ayuda()));                             // Se conecta el boton con mostrar_top()
    BotLy->addWidget(B4);

    //--------------------- Reloj ------------------------

    D_Clock_Timer = new DigitalClock();
    D_Clock_Timer->setFixedHeight(100);
    hbLy_info->addWidget(D_Clock_Timer);

    //-------------------- Top3 -------------------------
    QGroupBox* GB = new QGroupBox();

    hbLy_info->addWidget(GB);

    QVBoxLayout* TopLy = new QVBoxLayout(GB);

    QLabel* lbl_top3 = new QLabel("Top 3!!!");                      // Label Top3!!!
    lbl_top3->setAlignment(Qt::AlignCenter);
    QFont fuente2("MV Boli",25);
    lbl_top3->setFont(fuente2);
    TopLy->addWidget(lbl_top3);

    QFont fuente3("MV Boli",20);
    for (int i=0;i<3;i++)                                           // Labels con los 3 primeros del top
    {
        lbl_top3 = new QLabel();
        lbl_top3->setAlignment(Qt::AlignLeft);
        lbl_top3->setFont(fuente3);
        TopLy->addWidget(lbl_top3);
        Top3.append(lbl_top3);
    }
    actualizar_top3();                                              // Se actualiza el top

    /*start_game();                                                 //  Debug para hacer la ayuda
    px.load(QString("://IMG/Particulas/electron.png"));
    ListaFlip[6]->setPixmap(false,px);
    ListaFlip[6]->Flip();
    ListaFlip[12]->setPixmap(false,px);
    ListaFlip[12]->Flip();*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cargar_info()
{
    QFile f("icurc49.dll");           // Archivo de guardado
    QTextStream in(&f);


    if(!f.open(QIODevice::ReadOnly))        // Abriendolo
        qFatal("No puedo abrir el fichero para lectura.");

    in >> Nombre;

    for (int i=0;i<10;i++)                  // Lectura de los datos guardados
    {
        in >> ListaTop.Nombre[i];
        in >> ListaTop.H[i];
        in >> ListaTop.M[i];
        in >> ListaTop.S[i];
    }
    f.close();
}

void MainWindow::guardar_info()
{
    QFile f("icurc49.dll");           // Archivo de guardado
    QTextStream out(&f);

    if(!f.open(QIODevice::WriteOnly))        // Abriendolo
        qFatal("No puedo abrir el fichero para escritura.");

    out << Nombre << endl;

    for (int i=0;i<10;i++)                  // Escritura de los datos
    {
        out << ListaTop.Nombre[i] << " ";
        out << ListaTop.H[i] << " ";
        out << ListaTop.M[i] << " ";
        out << ListaTop.S[i];
        out << endl;
    }
    f.close();
}

void MainWindow::start_game()
{

    //------------------------ Comprobacion de que se desea iniciar un nuevo juego ---------------------
    if (Jugando)                                // Si ya se esta jugando
    {
        if (!Game_paused)                       // Si el juego no esta en pausa se pausa
            pause_unpause();

        new_game dlg;

        if (dlg.exec()!= QDialog::Accepted)     // Se pregunta si de verdad quiere empezar un juego nuevo
            return;                             // Si no aceptan, el juego espera a que se quite el pause para seguir
    }


    //----------------------- Juego nuevo -----------------------------------
    D_Clock_Timer->restart();                       // Se resetea el reloj
    D_Clock_Timer->stop();

    int A[36];      // Arreglo que contiene todas las cartas como enteros (ver setCardImage para saber que imagen corresponde a cada numero
    bool B[36];     // True para las cartas que no se han ubicado, false para las que si;

    int rand_number;    // Se almacena un numero aleatorio
    int i,j;            // Contadores

    for (i=0;i<36;i++)  // Se inicializan A y B
    {
        A[i]=i/2+1;
        B[i]=true;
    }

    QTime* T = new QTime(QTime::currentTime());     // Semilla del generador de num aleatorios
    qsrand(T->msec());                              // Se echa a andar el generador

    for (i=0;i<36;i++)                              // Para cada una de las 36 posiciones de las cartas
    {
        rand_number=qrand()%(36-i)+1;               // Se genera un numero aleatorio entre 1 y la cantidad de cartas que quedan por asignar
        j=0;

        while (rand_number!=0)                      // Se busca de las cartas que no se han asignado la que corresponde a rand_number
        {
            if (B[j])
            {
                rand_number--;
            }
            j++;
        }

        B[j-1]=false;                               // Se asigna esa con:
        setCardImage(i,A[j-1]);                     // su imagen
        ListaFlip[i]->setValor(A[j-1]);             // su valor
        ListaFlip[i]->setVisible(true);             // y se hace visible.
    }

    if (Game_paused)                                // Si el juego estaba en pausa se le quita
        pause_unpause();

    D_Clock_Timer->start();
    Jugando=true;                                   // Se actualiza el bool que indica que se esta jugando
}

void MainWindow::setCardImage(int i, int N)
{
    QPixmap px;

    switch (N)
    {
        case 1:
            px.load(QString("://IMG/Particulas/down.png"));
            break;
        case 2:
            px.load(QString("://IMG/Particulas/up.png"));
            break;
        case 3:
            px.load(QString("://IMG/Particulas/top.png"));
            break;
        case 4:
            px.load(QString("://IMG/Particulas/bottom.png"));
            break;
        case 5:
            px.load(QString("://IMG/Particulas/charm.png"));
            break;
        case 6:
            px.load(QString("://IMG/Particulas/strange.png"));
            break;
        case 7:
            px.load(QString("://IMG/Particulas/electron.png"));
            break;
        case 8:
            px.load(QString("://IMG/Particulas/tau.png"));
            break;
        case 9:
            px.load(QString("://IMG/Particulas/muon.png"));
            break;
        case 10:
            px.load(QString("://IMG/Particulas/elec_neut.png"));
            break;
        case 11:
            px.load(QString("://IMG/Particulas/tau_neut.png"));
            break;
        case 12:
            px.load(QString("://IMG/Particulas/muon_neut.png"));
            break;
        case 13:
            px.load(QString("://IMG/Particulas/foton.png"));
            break;
        case 14:
            px.load(QString("://IMG/Particulas/gluon.png"));
            break;
        case 15:
            px.load(QString("://IMG/Particulas/z_boson.png"));
            break;
        case 16:
            px.load(QString("://IMG/Particulas/w_boson.png"));
            break;
        case 17:
            px.load(QString("://IMG/Particulas/higgs.png"));
            break;
        case 18:
            px.load(QString("://IMG/Particulas/incognita.png"));
            break;

    }
    ListaFlip[i]->setPixmap(false,px);
}

void MainWindow::imagen_press(int i)
{
    if (Game_paused)            // el juego esta en pausa no se hace nada
        return;

    if (volteado==0)            // Si no hay cartas volteadas:
    {
        volteado=1;             // Se actualiza el contador
        ListaFlip[i]->Flip();   // Se voltea
        i_ant=i;                // Se almacena el indice de la primera carta

    }
    else if (volteado==1)       // Si habia una carta volteada:
    {
        volteado=2;             // Se actualiza el contador
        ListaFlip[i]->Flip();   // Se voltea la carta
        i_act=i;                // Se almacena el indice de la segunda carta
        comprobar_igual();      // Se comprueba si amabas son iguales
    }
    // OJO!!!
    // Si mientras hay dos cartas volteadas se hace click en otra, volteado=2 y no se hace nada
}

void MainWindow::comprobar_igual()
{
    if (ListaFlip[i_act]->getValor()==ListaFlip[i_ant]->getValor())         // Si los valores de ambas cartas son iguales:
    {        
        QTimer::singleShot(ListaFlip[0]->GetFlipDuration()+500, this, SLOT(espera_desaparecer()));  // Se espera a que la ultima carta acabe de voltear
                                                                                                    // y se mandan a desaparecer las dos
        p_elim++;           // Aumenta en uno las parejas eliminadas
        if (p_elim==18)     // Si se eliminaron las 18
            QTimer::singleShot(ListaFlip[0]->GetFlipDuration()+500, this, SLOT(game_over()));     // Se termino el juego



    }
    else
    {
        QTimer::singleShot(ListaFlip[0]->GetFlipDuration()+500, this, SLOT(espera_voltear()));      // Se espera a que la ultima carta acabe de voltear
                                                                                                    // y se mandan a voltear las dos        
    }
}

void MainWindow::espera_voltear()
{
    ListaFlip[i_act]->Flip();       // Volteo ambas cartas
    ListaFlip[i_ant]->Flip();
    volteado=0;
}

void MainWindow::espera_desaparecer()
{
    ListaFlip[i_act]->Flip();                   // Volteo ambas cartas
    ListaFlip[i_ant]->Flip();
    ListaFlip[i_act]->setVisible(false);        // Las hago invisibles
    ListaFlip[i_ant]->setVisible(false);
    volteado=0;                                 // Actualizo el contador a cero para que se puedan voltear cartas nuevas
}

void MainWindow::game_over()
{
    Jugando=false;                      // No se juega mas

    D_Clock_Timer->stop();              // Se para el tiempo

    int h = D_Clock_Timer->getTime().hour();        // Tiempo obtenido
    int m = D_Clock_Timer->getTime().minute();
    int s = D_Clock_Timer->getTime().second();

    int i_m;                            // Primer registro que desplaza si entra en el top10
    bool find = false;                  // Entra en el top

    for (int i=0;i<10;i++)              // Evaluar si entra en el top 10
    {
        if (h<ListaTop.H[i])            // Si la hora es menor
        {
            i_m=i;
            find=true;
            break;
        }
        else if ((h==ListaTop.H[i])&&(m<ListaTop.M[i]))     // Si las horas son iguales pero los min son menores
        {
            i_m=i;
            find=true;
            break;
        }
        else if ((h==ListaTop.H[i])&&(m==ListaTop.M[i])&&(s<ListaTop.S[i]))    // Si H y M son iguales pero los seg son menores
        {
            i_m=i;
            find=true;
            break;
        }
    }

    if (find)                           // Si entra en el top10
    {
        for (int i=9;i>i_m;i--)         // Desplazo todos los que tengan tiempos mayores
        {
            ListaTop.Nombre[i]=ListaTop.Nombre[i-1];
            ListaTop.H[i]=ListaTop.H[i-1];
            ListaTop.M[i]=ListaTop.M[i-1];
            ListaTop.S[i]=ListaTop.S[i-1];
        }

        ListaTop.Nombre[i_m]=Nombre;    // Agrego el nuevo registro en la posicion correspondiente
        ListaTop.H[i_m]=h;
        ListaTop.M[i_m]=m;
        ListaTop.S[i_m]=s;

        guardar_info();                 // Actualizo el archivo de guardado
    }

    if (find)                           // Si el tiempo esta entre los 3 mejores
    {
        juego_ganado dlg(true);         // Se muestra el dialogo de victoria
        dlg.exec();

        Top10 Dlg(ListaTop);            // Se muestra el top 10
        Dlg.exec();
    }
    else
    {
        juego_ganado dlg(false);         // Se muestra el dialogo de victoria
        dlg.exec();
    }


    if (i_m<3)                          // Si el nuevo record esta entre los tres primeros actualizar el top3
        actualizar_top3();
}

void MainWindow::pause_unpause()
{
    if (!Jugando)       // Si no se esta jugando no hacer nada
        return;

    QPixmap up,down;
    down = QPixmap("://IMG/Botones/pause_down.png");
    if (Game_paused)                    // Si el juego esta pausado
    {
        up = QPixmap("://IMG/Botones/pause_up.png");
        down = QPixmap("://IMG/Botones/pause_down.png");
        B2->changePixmap(up,down);
        D_Clock_Timer->start();         // Se echa a andar el reloj
        Game_paused=false;              // Se actualiza el booleano

    }
    else
    {
        up = QPixmap("://IMG/Botones/continue_up.png");
        down = QPixmap("://IMG/Botones/continue_down.png");
        B2->changePixmap(up,down);
        D_Clock_Timer->stop();          // Se para el reloj
        Game_paused=true;               // Se actualiza el booleano
    }
}

void MainWindow::mostrar_top()
{
    if (!Game_paused&&Jugando)           // Si el juego no esta en pausa se pausa.
        pause_unpause();

    Top10 Dlg(ListaTop);        // Se muestra el top 10
    Dlg.exec();
}

void MainWindow::mostrar_ayuda()
{
    if (!Game_paused&&Jugando)           // Si el juego no esta en pausa se pausa.
        pause_unpause();

    help Dlg;                         // Se muestra la ayuda
    Dlg.exec();
}

void MainWindow::cambiar_nombre()
{
    if (!Game_paused&&Jugando)           // Si el juego no esta en pausa se pausa.
        pause_unpause();

    Input_name dlg;

    if (dlg.exec()== QDialog::Accepted)     // Se lanza el dialogo que pide el nuevo nombre y se comprueba que se acepte
    {
        if (dlg.nombre()!="")               // Si el nombre no esta en blanco
        {
            Nombre=dlg.nombre();            // Se actualiza el nombre y se coloca en el label correspondiente

            QString QS("<p>Hi <b><i><u>" + Nombre + "</u></i></b><br> Click <a href=#>here</a> if this <br> is not your name</p>");
            lbl_name->setText(QS);

            guardar_info();                 // Se actualzia el archivo de los datos
        }
    }
}

void MainWindow::actualizar_top3()
{
    for (int i=0;i<3;i++)                   // Se actualiza el top3 con los datos de la lista del top10
    {
        QString QS(QString::number(i+1) + ".- " + ListaTop.Nombre[i]);
        Top3[i]->setText(QS);
    }
}

void MainWindow::prueba()
{
    Nombre = "Rachel";
    cambiar_nombre();
}
