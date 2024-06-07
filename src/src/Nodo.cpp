//
// Created by sebav on 07-06-2024.
//

#include "../include/Nodo.h"

Nodo::Nodo(transaccion *transacc) {

    transa = transacc;
    izquierdo = nullptr;
    derecho = nullptr;
    altura = 1;


}

Nodo::~Nodo() {
    delete transa;
    delete izquierdo;
    delete derecho;
}
