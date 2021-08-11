/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include "digitalclock.h"

//! [0]
DigitalClock::DigitalClock(QWidget *parent)
    : QLCDNumber(parent)
{
    //this->setStyleSheet("background-color: rgba(255, 255, 255, 64)");
    setSegmentStyle(Filled);
    setDigitCount(8);               // 8 Digitos en el 7segmento

    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));   // Siempre que pase 1s se activa showTime()

    Tiempo = QTime(0,0,0,0);                                    // Tiempo se inicia en 0
    QString text = Tiempo.toString();                           // Se convierte a texto
    display(text);                                              // Se muestra
}

void DigitalClock::start()
{
    timer->start(1000);                                         // Se inicia el timer y se programa para que de senhal cada 1s
    QString text = Tiempo.toString();                           // Se convierte a texto
    display(text);                                              // Se muestra
}

void DigitalClock::stop()
{
    timer->stop();                                              // Se detiene el timer
}

void DigitalClock::restart()
{
    Tiempo = QTime(0,0,0,0);                                    // Tiempo se pone a cero
    timer->start(1000);                                         // Se inicia el timer con periodo 1s
    QString text = Tiempo.toString();                           // Se convierte a texto
    display(text);                                              // Se muestra
}

QTime DigitalClock::getTime()
{
    return Tiempo;                                              // Se devuelve el tiempo
}
void DigitalClock::showTime()
{
    QTime Temp(Tiempo);
    Tiempo=Temp.addSecs(1);                     // Se aumenta el tiempo en 1s
    QString text = Tiempo.toString();           // Se convierte a texto
    if ((Tiempo.second() % 2) == 0)             // Efecto de aparecer y desaparecer los 2ptos
    {
        text[2] = ' ';
        text[5] = ' ';
    }
    display(text);                              // Se muestra el tiempo
}

