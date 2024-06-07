//
// Created by sebav on 07-06-2024.
//

#ifndef TALLERESTRUCTURA3_NODO_H
#define TALLERESTRUCTURA3_NODO_H
#include "transaccion.h"

class Nodo {

public:

    transaccion* transa;
    Nodo* izquierdo;
    Nodo* derecho;
    int altura;

    Nodo(transaccion* transacc);
    ~Nodo();

};


#endif //TALLERESTRUCTURA3_NODO_H
