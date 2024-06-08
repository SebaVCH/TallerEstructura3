//
// Created by sebav on 07-06-2024.
//

#include "../include/arbolAVL.h"

int arbolAVL::obtenerAltura(Nodo *nodo) {
    if (nodo == nullptr) return 0;
    return nodo->altura;

}

int arbolAVL::obtenerBalance(Nodo *nodo) {
    if (nodo == nullptr) return 0;
    return obtenerAltura(nodo->izquierdo) - obtenerAltura(nodo->derecho);
}

Nodo *arbolAVL::rotacionLL(Nodo *nodo) {
    Nodo* nuevaRaiz = nodo->izquierdo;
    nodo->izquierdo = nuevaRaiz->derecho;
    nuevaRaiz->derecho = nodo;

    nodo->altura = 1 + max(obtenerBalance(nodo->izquierdo), obtenerBalance(nodo->derecho));
    nuevaRaiz->altura = 1 + max(obtenerBalance(nuevaRaiz->izquierdo), obtenerBalance(nuevaRaiz->derecho));

    return nuevaRaiz;

}

Nodo *arbolAVL::rotacionRR(Nodo *nodo) {
    Nodo* nuevaRaiz = nodo->derecho;
    nodo->derecho = nuevaRaiz->izquierdo;
    nuevaRaiz->izquierdo = nodo;

    nodo->altura = 1 + max(obtenerBalance(nodo->izquierdo), obtenerBalance(nodo->derecho));
    nuevaRaiz->altura = 1 + max(obtenerBalance(nuevaRaiz->izquierdo), obtenerBalance(nuevaRaiz->derecho));

    return nuevaRaiz;

}

Nodo *arbolAVL::rotacionLR(Nodo *nodo) {
    rotacionRR(nodo->izquierdo);
    return rotacionLL(nodo);
}

Nodo *arbolAVL::rotacionRL(Nodo *nodo) {
    rotacionLL(nodo->derecho);
    return rotacionRR(nodo);
}

arbolAVL::arbolAVL() {

    raiz = nullptr;

}

arbolAVL::~arbolAVL() {

    delete raiz;

}

bool arbolAVL::buscarNodo(Nodo *raiz, string id) {
    if(raiz == nullptr) return false;
    if (id == raiz->transa->getID()){
        return true;
    } if (id < raiz->transa->getID()) {
        return buscarNodo(raiz->izquierdo,id);
    }
    return buscarNodo(raiz->derecho,id);

}

Nodo *arbolAVL::encontrarMinimo(Nodo *nodo) {

    Nodo* actual = nodo;

    while(actual->izquierdo != nullptr){
        actual = actual->izquierdo;
    }

    return actual;

}

Nodo *arbolAVL::insertarNodo(Nodo *raiz, transaccion *transa) {

    if (raiz == nullptr) return new Nodo(transa);


}






