//
// Created by sebav on 05-06-2024.
//

#ifndef TALLERESTRUCTURA3_PERSONA_H
#define TALLERESTRUCTURA3_PERSONA_H

#include <iostream>
using namespace std;

class persona {

private:

    string nombre;
    string rut;
    int saldoTotal;

public:

    persona(string nombre, string rut, int saldoTotal);
    string getNombre();
    string getRut();
    string getsaldoTotal();


};


#endif //TALLERESTRUCTURA3_PERSONA_H
