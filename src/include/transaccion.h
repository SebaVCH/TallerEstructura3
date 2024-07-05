//
// Created by sebav on 05-06-2024.
//

#ifndef TALLERESTRUCTURA3_TRANSACCION_H
#define TALLERESTRUCTURA3_TRANSACCION_H

#include <iostream>
using namespace std;

class transaccion {

private:

    //Atributos
    string ID;
    string cuenta_origen;
    string cuenta_destino;
    double monto;
    string fecha_hora;
    string Lugar;

    //Metodos para separar, transformar y calcular tiempo entre fechas
    int stringToInt(const string& str) const;
    void separarFechaHora(const string& fechaHora, int& dia, int& mes, int& anno, int& hora, int& minutos) const ;

public:

    //Constructor
    transaccion(string id, string origen, string destino, double monto, string fechaHora, string lugar);

    //Metodos getter
    string getID();
    string getCuentaOrigen();
    string getCuentaDestino();
    double getMonto();
    string getFechaHora();
    string getLugar();

    //Metodos setters
    void setCuentaOrigen(string cuentaOrigen);
    void setCuentaDestino(string cuentaDestino);
    void setMonto(double monto);
    void setFechaHora(string fechaHora);
    void setLugar(string lugar);

    //Metodo para calcular la diferencia en minuto entre 2 transacciones
    int calcularDiferenciaMinutos(transaccion* otraTransaccion) const;
};

#endif //TALLERESTRUCTURA3_TRANSACCION_H
