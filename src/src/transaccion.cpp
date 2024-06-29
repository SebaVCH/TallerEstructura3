//
// Created by sebav on 05-06-2024.
//

#include "../include/transaccion.h"

// Constructor
transaccion::transaccion(string id, string origen, string destino, double monto, string fechaHora) {
    ID = id;
    cuenta_origen = origen;
    cuenta_destino = destino;
    this->monto = monto;
    fecha_hora = fechaHora;
}

string transaccion::getID() {
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

void transaccion::setCuentaOrigen(string cuentaOrigen) {
    cuenta_origen = cuentaOrigen;
}

void transaccion::setCuentaDestino(string cuentaDestino) {
    cuenta_destino = cuentaDestino;
}

void transaccion::setMonto(double monto) {
    transaccion::monto = monto;
}

void transaccion::setFechaHora(string fechaHora) {
    fecha_hora = fechaHora;
}
