#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../include/arbolAVL.h"

using namespace std;
//g++ src/src/*.cpp -o taller
//./taller

//3 lugares donde se pide la ruta del txt
//"D:/Programas/c++ workspace visual/taller3/TallerEstructura3/src/data/listadoTransacciones.txt"


// Menu
void mostrarMenu(arbolAVL*& avl);

// Funciones a utilizar
void agregarNuevaTransa(arbolAVL*& avl);
void buscarTransa(arbolAVL*& avl);
void eliminarTransa(arbolAVL*& avl);
void modificarTransa(arbolAVL*& avl);
void cargarTransaccionesDesdeArchivo(arbolAVL*& avl, const string& nombreArchivo);
void guardarTransaccionEnArchivo(const string& nombreArchivo, transaccion* nuevaTransa);
void definirMontoSospechoso(int &maximoOriginal);
void definirLapsoDeTiempoYFrecuencia(int &difEntreTran, int &cantMax);
void definirMaximoDeHoras(int &horasMinimas);

int main() {
    arbolAVL* arbolTransacciones = new arbolAVL();
    cargarTransaccionesDesdeArchivo(arbolTransacciones, "D:/Programas/c++ workspace visual/taller3/TallerEstructura3/src/data/listadoTransacciones.txt");
    mostrarMenu(arbolTransacciones);

    delete arbolTransacciones;
    return 0;
}

void mostrarMenu(arbolAVL* &avl) {

    int montoMaximo = 10000;

    int diferenciaEntreTransacciones = 60; //En minutos
    int cantMaxDeTransferencias = 5;

    int diferenciaMaximaDeHoras = 12; //Tiempo de espera en horas, entre diferentes zonas geograficas

    int opcion;

    do {
        cout << "***** BANCO *****" << endl;
        cout << "1. Ingresar nueva transaccion" << endl;
        cout << "2. Buscar transaccion" << endl;
        cout << "3. Modificar transaccion" << endl;
        cout << "4. Buscar historial de transacciones sospechosas" << endl;
        cout << "5. Definir criterios para transacciones sospechosas" << endl;
        cout << "6. Salir" << endl;
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                agregarNuevaTransa(avl);
                break;
            case 2:
                buscarTransa(avl);
                break;
            case 3:
                cout << "Indique que el numero del tipo de modificacion que desea realizar:" << endl;
                cout << "1. Modificar parametros de una transaccion" << endl;
                cout << "2. Eliminar una transaccion" << endl;
                cout << "3. Salir" << endl;
                cin >> opcion;

                switch (opcion) {
                    case 1:
                        modificarTransa(avl);
                        break;
                    case 2:
                        eliminarTransa(avl);
                        break;
                    case 3:
                        cout << "Regresando al menu del banco..." << endl;
                        break;
                    default:
                        cout << "Opcion no valida. Por favor, ingrese un numero valido." << endl;
                        break;
                }
                break;
            case 4:
                break;
            case 5:
                cout << "Indique que el numero del criterio que desea modificar:" << endl;
                cout << "1. Monto maximo a transferir" << endl;
                cout << "2. Lapso de tiempo entre transacciones" << endl;
                cout << "3. Salir" << endl;
                cin >> opcion;

                switch (opcion) {
                    case 1:
                        definirMontoSospechoso(montoMaximo);
                        break;
                    case 2:
                        definirLapsoDeTiempoYFrecuencia(diferenciaEntreTransacciones,cantMaxDeTransferencias);
                        break;
                    case 3:
                        definirMaximoDeHoras(diferenciaMaximaDeHoras);
                        break;
                    case 4:
                        cout << "Regresando al menu del banco..." << endl;
                        break;
                    default:
                        cout << "Opcion no valida. Por favor, ingrese un numero valido." << endl;
                        break;
                }
                break;
            case 6:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion no valida. Por favor, ingrese un numero valido." << endl;
                break;
        }
    } while (opcion != 6);
}

void eliminarTransa(arbolAVL*& avl) {
    string ID;
    cout << "Indique el ID de la transaccion a eliminar: ";
    cin >> ID;

    if (avl->eliminar(ID)) {
        cout << "Se ha borrado la transaccion con exito." << endl;
    } else {
        cout << "No se ha borrado nada dado que la transaccion no existe." << endl;
    }
}
void modificarTransa(arbolAVL*& avl) {
    string idTransaccion;
    cout << "Ingrese ID de la transaccion a modificar: ";
    cin >> idTransaccion;

    Nodo* transaAModificar = avl->buscar(idTransaccion);

    if (transaAModificar == nullptr) {
        cout << "Error: Transaccion con ID " << idTransaccion << " no encontrada." << endl;
        return;
    }

    string nuevaCuentaOrigen;
    cout << "Ingrese nuevo numero de cuenta de origen (actual: " << transaAModificar->transa->getCuentaOrigen() << "): ";
    cin >> nuevaCuentaOrigen;

    string nuevaCuentaDestino;
    cout << "Ingrese nuevo numero de cuenta de destino (actual: " << transaAModificar->transa->getCuentaDestino() << "): ";
    cin >> nuevaCuentaDestino;

    double nuevoMonto;
    cout << "Ingrese nuevo monto de la transaccion (actual: " << transaAModificar->transa->getMonto() << "): ";
    cin >> nuevoMonto;

    string nuevaFechaHora;
    cout << "Ingrese nueva fecha y hora (actual: " << transaAModificar->transa->getFechaHora() << "): ";
    cin >> nuevaFechaHora;

    transaAModificar->transa->setCuentaOrigen(nuevaCuentaOrigen);
    transaAModificar->transa->setCuentaDestino(nuevaCuentaDestino);
    transaAModificar->transa->setMonto(nuevoMonto);
    transaAModificar->transa->setFechaHora(nuevaFechaHora);

    cout << "Transaccion con ID " << idTransaccion << " modificada exitosamente." << endl;
}
void buscarTransa(arbolAVL*& avl) {
    string ID;
    cout << "Indique el ID de la transaccion a buscar: ";
    cin >> ID;

    if (avl->buscar(ID)) {
        cout << "La transaccion si existe y esta en nuestra base de datos." << endl;
    } else {
        cout << "La transaccion no existe. Por favor digite correctamente el ID de la transaccion o agreguela manualmente." << endl;
    }
}
void agregarNuevaTransa(arbolAVL*& avl) {

    //Generar ID nuevo respecto al ultimo
    ifstream archivo("D:/Programas/c++ workspace visual/taller3/TallerEstructura3/src/data/listadoTransacciones.txt");
    string linea;
    int maxID = 0;
    while (getline(archivo, linea)) {
        if (linea.length() > 3 && linea[0] >= '0' && linea[0] <= '9') {
            int id = stoi(linea.substr(0, 3));
            maxID = max(maxID, id);
        }
    }
    archivo.close();

    string nuevoID = to_string(maxID + 1);
    while (nuevoID.length() < 3) {
        nuevoID = "0" + nuevoID;
    }

    string cuenta_origen;
    cout << "Ingrese numero de cuenta de origen: ";
    cin >> cuenta_origen;

    string cuenta_destino;
    cout << "Ingrese numero de cuenta de destino: ";
    cin >> cuenta_destino;

    double monto;
    cout << "Ingrese monto de la transaccion: ";
    cin >> monto;

    string fecha_hora;
    cout << "Ingrese fecha y hora(DD/MM/AAAA-HH:mm): ";
    cin >> fecha_hora;

    transaccion* nuevaTransa = new transaccion(nuevoID, cuenta_origen, cuenta_destino, monto, fecha_hora);
    avl->insertar(nuevaTransa);
    guardarTransaccionEnArchivo("D:/Programas/c++ workspace visual/taller3/TallerEstructura3/src/data/listadoTransacciones.txt", nuevaTransa);

    cout << "Transaccion agregada exitosamente con ID: " << nuevoID << endl;
}
void cargarTransaccionesDesdeArchivo(arbolAVL*& avl, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de transacciones." << endl;
        return;
    }

    string linea, id, cuentaOrigen, cuentaDestino, fechaHora;
    double monto;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, id, ',');
        getline(ss, cuentaOrigen, ',');
        getline(ss, cuentaDestino, ',');
        ss >> monto;
        ss.ignore(1, ',');
        getline(ss, fechaHora);

        transaccion* transa = new transaccion(id, cuentaOrigen, cuentaDestino, monto, fechaHora);
        avl->insertar(transa);
    }

    archivo.close();
}
void guardarTransaccionEnArchivo(const string& nombreArchivo, transaccion* nuevaTransa) {
    ofstream archivo(nombreArchivo, ios::app);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de transacciones." << endl;
        return;
    }

    archivo << endl
            << nuevaTransa->getID() << ','
            << nuevaTransa->getCuentaOrigen() << ','
            << nuevaTransa->getCuentaDestino() << ','
            << nuevaTransa->getMonto() << ','
            << nuevaTransa->getFechaHora();

    archivo.close();
}
void definirMontoSospechoso(int &maximoOriginal) {
    cout << "Indique el monto para definir que una transaccion es sospechosa: ";
    cin >> maximoOriginal;
}
void definirLapsoDeTiempoYFrecuencia(int &difEntreTran, int &cantMax) {

    cout << "Indique la cantidad maxima de transacciones: ";
    cin >> cantMax;
    cout << "Indique el periodo de tiempo en el que puedan ocurrir como maximo " << cantMax << " transacciones: ";
    cin >> difEntreTran;

}
void definirMaximoDeHoras(int &horasMinimas) {

    cout << "Indique el minimo de horas que debe haber para realizar una transaccion en diferentes ubicaciones geograficas: ";
    cin >> horasMinimas;

}