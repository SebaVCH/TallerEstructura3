//
// Created by sebav on 07-06-2024.
//

#ifndef TALLERESTRUCTURA3_NODO_H
#define TALLERESTRUCTURA3_NODO_H
#include "transaccion.h"

class Nodo {

public:

    //Atributos
    transaccion* transa;
    Nodo* izquierdo;
    Nodo* derecho;
    int altura;

    //Constructor y destructor
    Nodo(transaccion* transacc);
    ~Nodo();

};


#endif //TALLERESTRUCTURA3_NODO_H
