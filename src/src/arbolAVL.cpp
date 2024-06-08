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

    if (transa->getID() < raiz->transa->getID()) {
        raiz->izquierdo = insertarNodo(raiz->izquierdo,transa);
    }
    if (transa->getID() > raiz->transa->getID()) {
        raiz->derecho = insertarNodo(raiz->derecho,transa);
    } else {
        return raiz;
    }

    raiz->altura = 1 + max(obtenerAltura(raiz->izquierdo), obtenerBalance(raiz->derecho));
    int balance = obtenerBalance(raiz);

    if(balance > 1 && transa->getID() < raiz->izquierdo->transa->getID()){
        return rotacionLL(raiz);
    } if(balance < -1 && transa->getID() > raiz->derecho->transa->getID()){
        return rotacionRR(raiz);
    }if(balance > 1 && transa->getID() > raiz->izquierdo->transa->getID()){
        return rotacionLR(raiz);
    } if(balance < -1 && transa->getID() < raiz->derecho->transa->getID()){
        return rotacionRL(raiz);
    }

    return raiz;

}

void arbolAVL::insertar(transaccion *transa) {
    raiz = insertarNodo(raiz,transa);
}






