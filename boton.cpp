#include "boton.h"

#include <QMouseEvent>
#include <QString>

Boton::Boton(QPixmap up, QPixmap down,int w,int h, QWidget *parent)
{
    u= up;
    d= down;




    setPixmap(u);
    setAlignment(Qt::AlignCenter);

    setFixedHeight(h);
    setFixedWidth(w);

}

void Boton::getMouseDown()
{

}

void Boton::changePixmap(QPixmap up, QPixmap down)
{
    u= up;
    d= down;
    setPixmap(u);
}

void Boton::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton)
    {
        setPixmap(d);

    }

}

void Boton::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton)
    {
        setPixmap(u);
        emit linkActivated("ok");
    }
}
