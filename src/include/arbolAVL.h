//
// Created by sebav on 07-06-2024.
//

#ifndef TALLERESTRUCTURA3_ARBOLAVL_H
#define TALLERESTRUCTURA3_ARBOLAVL_H

#include <queue>
#include "Nodo.h"
using namespace std;

class arbolAVL {

private:

    Nodo* raiz;

    //Extras
    int obtenerAltura(Nodo* nodo);
    int obtenerBalance(Nodo* nodo);
    Nodo* encontrarMinimo(Nodo* nodo);

    //Balance
    Nodo* rotacionLL(Nodo* nodo);
    Nodo* rotacionRR(Nodo* nodo);
    Nodo* rotacionLR(Nodo* nodo);
    Nodo* rotacionRL(Nodo* nodo);

    //Metodos importantes
    Nodo* insertarNodo(Nodo* raiz, transaccion* transa);
    Nodo* eliminarNodo(Nodo* raiz, string id, bool& eliminado);
    Nodo* buscarNodo(Nodo* raiz,string id);

    //Encontrar transacciones sospechosas
    void encontrarTransaccionesFrecuentes(Nodo* nodo, queue<transaccion*>& transaccionesRecientes, int diferenciaEntreTransacciones, int cantMaxDeTransferencias, arbolAVL* &Sospechoso);
    void encontrarTransaccionesPorUbicacion(Nodo* nodo, queue<transaccion*>& transaccionesRecientes, int diferenciaMaximaDeHoras, arbolAVL* &Sospechoso);


public:

    arbolAVL();
    ~arbolAVL();

    //Acciones principales
    void insertar(transaccion* transa);
    bool eliminar(string id);
    Nodo* buscar(string id);
    Nodo* obtenerRaiz();

    //Obtencion de sospechosos
    void obtenerSospechososMontoMaximo(Nodo *nodo, arbolAVL *&Sospechoso,int montoMaximo);
    void obtenerSospechososFrecuencia(int diferenciaEntreTransacciones, int cantMaxDeTransferencias, arbolAVL* &Sospechoso);
    void obtenerSospechososPorUbicacion(int diferenciaMaximaDeHoras, arbolAVL* &Sospechoso);

    //Prints de sospechosos
    void printTransaccionesSospechosas(Nodo* nodo);


};


#endif //TALLERESTRUCTURA3_ARBOLAVL_H
