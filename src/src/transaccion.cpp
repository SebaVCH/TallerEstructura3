//
// Created by sebav on 05-06-2024.
//

#include <sstream>
#include "../include/transaccion.h"

// Constructor
transaccion::transaccion(string id, string origen, string destino, double monto, string fechaHora, string lugar) {
    ID = id;
    cuenta_origen = origen;
    cuenta_destino = destino;
    this->monto = monto;
    fecha_hora = fechaHora;
    Lugar=lugar;
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

string transaccion::getLugar() {
    return Lugar;
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

void transaccion::setLugar(string lugar) {
    Lugar = lugar;
}

int transaccion::stringToInt(const string& str) const {
    stringstream ss(str);
    int num;
    ss >> num;
    return num;
}

void transaccion::separarFechaHora(const string& fechaHora, int& dia, int& mes, int& anno, int& hora, int& minutos) const {
    dia = stringToInt(fechaHora.substr(0, 2));
    mes = stringToInt(fechaHora.substr(3, 2));
    anno = stringToInt(fechaHora.substr(6, 4));
    hora = stringToInt(fechaHora.substr(11, 2));
    minutos = stringToInt(fechaHora.substr(14, 2));
}

int transaccion::calcularDiferenciaMinutos(transaccion* otraTransaccion) const {
    int dia1, mes1, anno1, hora1, minutos1;
    int dia2, mes2, anno2, hora2, minutos2;

    separarFechaHora(fecha_hora, dia1, mes1, anno1, hora1, minutos1);
    separarFechaHora(otraTransaccion->getFechaHora(), dia2, mes2, anno2, hora2, minutos2);

    int totalMinutos1 = ((anno1 * 365 + mes1 * 30 + dia1) * 24 + hora1) * 60 + minutos1;
    int totalMinutos2 = ((anno2 * 365 + mes2 * 30 + dia2) * 24 + hora2) * 60 + minutos2;

    return abs(totalMinutos2 - totalMinutos1);
}
