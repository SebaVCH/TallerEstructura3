//
// Created by sebav on 07-06-2024.
//

#ifndef TALLERESTRUCTURA3_ARBOLAVL_H
#define TALLERESTRUCTURA3_ARBOLAVL_H
#include "Nodo.h"

class arbolAVL {

private:

    Nodo* raiz;

public:

    //Extras
    int obtenerAltura(Nodo* nodo);
    int obtenerBalance(Nodo* nodo);
    Nodo* encontrarMinimo(Nodo* raiz);

    //Balances
    Nodo* rotacionLL(Nodo* nodo);
    Nodo* rotacionRR(Nodo* nodo);
    Nodo* rotacionLR(Nodo* nodo);
    Nodo* rotacionRL(Nodo* nodo);

    //Funciones importantes
    Nodo* insertar(Nodo* raiz, transaccion* transa);
    Nodo* eliminar(Nodo* raiz, int id);
    bool buscar(Nodo* raiz, int id);
    void inorder(Nodo* raiz);

};


#endif //TALLERESTRUCTURA3_ARBOLAVL_H
