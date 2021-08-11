#ifndef BOTON_H
#define BOTON_H

#include <QLabel>
#include <QPixmap>

class Boton : public QLabel
{
public:
    Boton(QPixmap up, QPixmap down, int w, int h, QWidget* parent = NULL );
    void getMouseDown();
    void changePixmap(QPixmap up, QPixmap down);

protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);

private:
    QPixmap u;
    QPixmap d;
signals:
};

#endif // BOTON_H
