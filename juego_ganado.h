#ifndef JUEGO_GANADO_H
#define JUEGO_GANADO_H

#include <QDialog>

namespace Ui {
class juego_ganado;
}

class juego_ganado : public QDialog
{
    Q_OBJECT
    
public:
    explicit juego_ganado(bool top, QWidget *parent = 0);
    ~juego_ganado();
    
private:
    Ui::juego_ganado *ui;
};

#endif // JUEGO_GANADO_H
