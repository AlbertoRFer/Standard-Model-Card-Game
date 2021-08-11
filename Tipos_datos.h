#ifndef TIPOS_DATOS_H
#define TIPOS_DATOS_H

class QString;
class QTime;

struct Top      // Tipo de dato para manejar el top10
{
    QString Nombre[10];     //  10 nombres
    int H[10];              //  10 horas
    int M[10];              //  10 minutos
    int S[10];              //  10 segundos
};

#endif // TIPOS_DATOS_H
