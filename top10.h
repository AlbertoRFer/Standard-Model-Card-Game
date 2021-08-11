#ifndef TOP10_H
#define TOP10_H

#include <QDialog>
#include "Tipos_datos.h"

namespace Ui {
class Top10;
}

class Top10 : public QDialog
{
    Q_OBJECT
    
public:
    explicit Top10(Top Lista, QWidget *parent = 0);
    ~Top10();
    
private:
    Ui::Top10 *ui;
};

#endif // TOP10_H
