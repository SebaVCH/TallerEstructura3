//
// Created by sebav on 05-06-2024.
//

#ifndef TALLERESTRUCTURA3_TRANSACCION_H
#define TALLERESTRUCTURA3_TRANSACCION_H

#include <iostream>
using namespace std;

class transaccion {

private:
    int ID;
    string cuenta_origen;
    string cuenta_destino;
    double monto;
    string fecha_hora;

public:
    transaccion(int id, string origen, string destino, double monto, string fechaHora);

    int getID();
    string getCuentaOrigen();
    string getCuentaDestino();
    double getMonto();
    string getFechaHora();
};

#endif //TALLERESTRUCTURA3_TRANSACCION_H
