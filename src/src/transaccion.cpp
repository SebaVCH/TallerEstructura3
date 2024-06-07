//
// Created by sebav on 05-06-2024.
//

#include "../include/transaccion.h"

// Constructor
transaccion::transaccion(int id, string origen, string destino, double monto, string fechaHora) {
    ID = id;
    cuenta_origen = origen;
    cuenta_destino = destino;
    this->monto = monto;
    fecha_hora = fechaHora;
}

int transaccion::getID() {
    return ID;
}

string transaccion::getCuentaOrigen() {
    return cuenta_origen;
}

string transaccion::getCuentaDestino() {
    return cuenta_destino;
}

double transaccion::getMonto() {
    return monto;
}

string transaccion::getFechaHora() {
    return fecha_hora;
}