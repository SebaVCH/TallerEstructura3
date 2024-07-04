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
    try {
        Nodo* nuevaRaiz = nodo->izquierdo;
        nodo->izquierdo = nuevaRaiz->derecho;
        nuevaRaiz->derecho = nodo;

        nodo->altura = 1 + max(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho));
        nuevaRaiz->altura = 1 + max(obtenerAltura(nuevaRaiz->izquierdo), obtenerAltura(nuevaRaiz->derecho));

        return nuevaRaiz;
    } catch (const std::bad_alloc &e) {
        std::cerr << "Error de asignación de memoria: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

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

Nodo* arbolAVL::buscarNodo(Nodo* raiz, string id) {
    if (raiz == nullptr) return nullptr;

    if (id == raiz->transa->getID()) {
        return raiz;
    } else if (id < raiz->transa->getID()) {
        return buscarNodo(raiz->izquierdo, id);
    } else {
        return buscarNodo(raiz->derecho, id);
    }
}

Nodo *arbolAVL::encontrarMinimo(Nodo *nodo) {

    Nodo* actual = nodo;

    while(actual->izquierdo != nullptr){
        actual = actual->izquierdo;
    }

    return actual;

}

Nodo *arbolAVL::insertarNodo(Nodo *raiz, transaccion *transa) {

    if (raiz == nullptr) {
        try {
            return new Nodo(transa);
        } catch (const std::bad_alloc &e) {
            std::cerr << "Error de asignación de memoria: " << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }
    }

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
Nodo* arbolAVL::buscar(string id) {
    Nodo* nodoEncontrado = buscarNodo(raiz, id);
    return nodoEncontrado;
}

bool arbolAVL::eliminar(string id) {
    bool eliminado = false;
    raiz = eliminarNodo(raiz, id, eliminado);
    return eliminado;
}

Nodo* arbolAVL::eliminarNodo(Nodo* raiz, string id, bool& eliminado) {
    if (raiz == nullptr) return raiz;

    if (id < raiz->transa->getID()) {
        raiz->izquierdo = eliminarNodo(raiz->izquierdo, id, eliminado);
    } else if (id > raiz->transa->getID()) {
        raiz->derecho = eliminarNodo(raiz->derecho, id, eliminado);
    } else {
        eliminado = true;
        if (raiz->izquierdo == nullptr && raiz->derecho == nullptr) {
            delete raiz;
            raiz = nullptr;
        } else if (raiz->izquierdo == nullptr) {
            Nodo* temp = raiz->derecho;
            delete raiz;
            raiz = temp;
        } else if (raiz->derecho == nullptr) {
            Nodo* temp = raiz->izquierdo;
            delete raiz;
            raiz = temp;
        } else {
            Nodo* temp = encontrarMinimo(raiz->derecho);
            raiz->transa = temp->transa;
            raiz->derecho = eliminarNodo(raiz->derecho, temp->transa->getID(), eliminado);
        }
    }

    if (raiz == nullptr) return raiz;

    raiz->altura = 1 + max(obtenerAltura(raiz->izquierdo), obtenerAltura(raiz->derecho));

    int balance = obtenerBalance(raiz);

    if (balance > 1 && obtenerBalance(raiz->izquierdo) >= 0) {
        return rotacionLL(raiz);
    }
    if (balance > 1 && obtenerBalance(raiz->izquierdo) < 0) {
        return rotacionLR(raiz);
    }
    if (balance < -1 && obtenerBalance(raiz->derecho) <= 0) {
        return rotacionRR(raiz);
    }
    if (balance < -1 && obtenerBalance(raiz->derecho) > 0) {
        return rotacionRL(raiz);
    }

    return raiz;
}

Nodo *arbolAVL::obtenerRaiz() {
    return raiz;
}

void arbolAVL::obtenerSospechososMontoMaximo(Nodo *nodo, arbolAVL *&Sospechoso, int montoMaximo) {

    if (nodo == nullptr) {
        return;
    }

    obtenerSospechososMontoMaximo(nodo->izquierdo, Sospechoso,montoMaximo);

    if (nodo->transa->getMonto() > montoMaximo) {
        Sospechoso->insertar(nodo->transa);
    }

    obtenerSospechososMontoMaximo(nodo->derecho, Sospechoso,montoMaximo);

}

void arbolAVL::printTransaccionesSospechosas(Nodo *nodo) {

    if (nodo == nullptr) {
        return;
    }

    printTransaccionesSospechosas(nodo->izquierdo);

    cout << "ID: " << nodo->transa->getID() << endl;
    cout << "Cuenta de origen: " << nodo->transa->getCuentaOrigen() << endl;
    cout << "Cuenta de destino: " << nodo->transa->getCuentaDestino() << endl;
    cout << "Monto: " << nodo->transa->getMonto() << endl;
    cout << "Fecha y hora: " << nodo->transa->getFechaHora() << endl;
    cout << "Ubicacion: " << nodo->transa->getLugar() << endl;
    cout << "-----------------------------" << endl;

    printTransaccionesSospechosas(nodo->derecho);

}

void arbolAVL::encontrarTransaccionesFrecuentes(Nodo* nodo, queue<transaccion*>& transaccionesRecientes, int diferenciaEntreTransacciones, int cantMaxDeTransferencias, arbolAVL*& Sospechoso) {
    if (nodo == nullptr) {
        return;
    }

    encontrarTransaccionesFrecuentes(nodo->izquierdo, transaccionesRecientes, diferenciaEntreTransacciones, cantMaxDeTransferencias, Sospechoso);

    transaccionesRecientes.push(nodo->transa);

    while (!transaccionesRecientes.empty() && transaccionesRecientes.front()->calcularDiferenciaMinutos(nodo->transa) > diferenciaEntreTransacciones) {
        transaccionesRecientes.pop();
    }

    int count = 0;
    queue<transaccion*> transaccionesTemp = transaccionesRecientes;
    while (!transaccionesTemp.empty()) {
        if (transaccionesTemp.front()->getCuentaOrigen() == nodo->transa->getCuentaOrigen()) {
            count++;
        }
        transaccionesTemp.pop();
    }

    if (count > cantMaxDeTransferencias) {
        Sospechoso->insertar(nodo->transa);
    }

    encontrarTransaccionesFrecuentes(nodo->derecho, transaccionesRecientes, diferenciaEntreTransacciones, cantMaxDeTransferencias, Sospechoso);
}


void arbolAVL::obtenerSospechososFrecuencia(int diferenciaEntreTransacciones, int cantMaxDeTransferencias,arbolAVL *&Sospechoso) {

    queue<transaccion*> transaccionesRecientes;
    encontrarTransaccionesFrecuentes(raiz, transaccionesRecientes, diferenciaEntreTransacciones, cantMaxDeTransferencias, Sospechoso);

}

void arbolAVL::obtenerSospechososPorUbicacion(int diferenciaMaximaDeHoras, arbolAVL* &Sospechoso) {
    queue<transaccion*> transaccionesRecientes;
    encontrarTransaccionesPorUbicacion(raiz, transaccionesRecientes, diferenciaMaximaDeHoras, Sospechoso);
}

void arbolAVL::encontrarTransaccionesPorUbicacion(Nodo* nodo, queue<transaccion*>& transaccionesRecientes, int diferenciaMaximaDeHoras, arbolAVL*& Sospechoso) {
    if (nodo == nullptr) {
        return;
    }

    encontrarTransaccionesPorUbicacion(nodo->izquierdo, transaccionesRecientes, diferenciaMaximaDeHoras, Sospechoso);

    transaccionesRecientes.push(nodo->transa);

    while (!transaccionesRecientes.empty() && transaccionesRecientes.front()->calcularDiferenciaMinutos(nodo->transa) / 60 > diferenciaMaximaDeHoras) {
        transaccionesRecientes.pop();
    }

    string cuentaOrigenActual = nodo->transa->getCuentaOrigen();
    string lugarActual = nodo->transa->getLugar();

    queue<transaccion*> transaccionesTemp = transaccionesRecientes;
    while (!transaccionesTemp.empty()) {
        transaccion* transaTemp = transaccionesTemp.front();
        transaccionesTemp.pop();

        if (transaTemp->getCuentaOrigen() == cuentaOrigenActual) {
            if (transaTemp->getLugar() != lugarActual) {
                int diferenciaHoras = transaTemp->calcularDiferenciaMinutos(nodo->transa) / 60;
                if (diferenciaHoras <= diferenciaMaximaDeHoras) {
                    Sospechoso->insertar(nodo->transa);
                    break;
                }
            }
        }
    }

    encontrarTransaccionesPorUbicacion(nodo->derecho, transaccionesRecientes, diferenciaMaximaDeHoras, Sospechoso);
}

