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
    string Lugar;

    int stringToInt(const string& str) const;
    void separarFechaHora(const string& fechaHora, int& dia, int& mes, int& anno, int& hora, int& minutos) const ;

public:
    transaccion(string id, string origen, string destino, double monto, string fechaHora, string lugar);

    string getID();
    string getCuentaOrigen();
    string getCuentaDestino();
    double getMonto();
    string getFechaHora();
    string getLugar();

    void setCuentaOrigen(string cuentaOrigen);
    void setCuentaDestino(string cuentaDestino);
    void setMonto(double monto);
    void setFechaHora(string fechaHora);
    void setLugar(string lugar);

    int calcularDiferenciaMinutos(transaccion* otraTransaccion) const;
};

#endif //TALLERESTRUCTURA3_TRANSACCION_H
