//
// Created by sebav on 05-06-2024.
//

#ifndef TALLERESTRUCTURA3_TRANSACCION_H
#define TALLERESTRUCTURA3_TRANSACCION_H

#include <iostream>
using namespace std;

class transaccion {

private:
    string ID;
    string cuenta_origen;
    string cuenta_destino;
    double monto;
    string fecha_hora;

public:
    transaccion(string id, string origen, string destino, double monto, string fechaHora);

    string getID();
    string getCuentaOrigen();
    string getCuentaDestino();
    double getMonto();
    string getFechaHora();

    void setCuentaOrigen(string cuentaOrigen);
    void setCuentaDestino(string cuentaDestino);
    void setMonto(double monto);
    void setFechaHora(string fechaHora);

};

#endif //TALLERESTRUCTURA3_TRANSACCION_H
