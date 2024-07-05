#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include "../include/arbolAVL.h"

using namespace std;
//g++ src/src/*.cpp -o taller
//./taller

//9 lugares donde se pide la ruta del txt
//"D:/Programas/c++ workspace visual/taller3/TallerEstructura3/src/data/listadoTransacciones.txt"
///"workspaces/TallerEstructura2/src/data/listadoTransacciones.txt"

// Menu
void mostrarMenu(arbolAVL*& avl);

// Funciones principales
void agregarNuevaTransa(arbolAVL*& avl);
void buscarTransa(arbolAVL*& avl);
void eliminarTransa(arbolAVL*& avl);
void modificarTransa(arbolAVL*& avl);
void definirMontoSospechoso(int &maximoOriginal);
void definirLapsoDeTiempoYFrecuencia(int &difEntreTran, int &cantMax);
void definirMaximoDeHoras(int &horasMinimas);
void reporteTransaccionesSospechosas(arbolAVL *&Avl, arbolAVL *&Sospechoso,int maximo, int transacciones, int transferencias, int horas);

//Cargado y guardado de archivos
void cargarTransaccionesDesdeArchivo(arbolAVL*& avl, const string& nombreArchivo);
void guardarTransaccionEnArchivo(const string& nombreArchivo, transaccion* nuevaTransa);
void eliminarLineaTXT(string ID);
void modificarLineaTXT(const string& nombreArchivo, const string& idTransaccion, const string& nuevaLinea);


int main() {
    arbolAVL* arbolTransacciones = new arbolAVL();
    cargarTransaccionesDesdeArchivo(arbolTransacciones, "/workspaces/TallerEstructura3/src/data/listadoTransacciones.txt");
    mostrarMenu(arbolTransacciones);

    delete arbolTransacciones;
    return 0;
}

void mostrarMenu(arbolAVL* &avl) {

    //Arbol de sospechas
    arbolAVL* arbolSospechoso = new arbolAVL();

    //Variables de sospecha
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
                cout << "Ingrese su opcion: ";
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
                reporteTransaccionesSospechosas(avl,arbolSospechoso,montoMaximo,diferenciaEntreTransacciones,cantMaxDeTransferencias,diferenciaMaximaDeHoras);
                break;
            case 5:
                cout << "Indique que el numero del criterio que desea modificar:" << endl;
                cout << "1. Monto maximo a transferir" << endl;
                cout << "2. Lapso de tiempo entre transacciones" << endl;
                cout << "3. Definir Maximo De Horas de espera entre zonas geograficas" << endl;
                cout << "4. Salir" << endl;
                cout << "Ingrese su opcion: ";
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

void reporteTransaccionesSospechosas(arbolAVL *&Avl, arbolAVL *&Sospechoso,int montoMaximo, int diferenciaEntreTransacciones, int cantMaxDeTransferencias, int diferenciaMaximaDeHoras) {

    Avl->obtenerSospechososMontoMaximo(Avl->obtenerRaiz(),Sospechoso,montoMaximo);
    cout << "=== Transacciones sospechosas por monto maximo excedido ===" << endl;
    Sospechoso->printTransaccionesSospechosas(Sospechoso->obtenerRaiz());
    cout << endl;

    // Reiniciar arbol sospechoso
    delete Sospechoso;
    Sospechoso = new arbolAVL();

    Avl->obtenerSospechososFrecuencia(diferenciaEntreTransacciones, cantMaxDeTransferencias, Sospechoso);
    cout << "=== Transacciones sospechosas por frecuencia ===" << endl;
    Sospechoso->printTransaccionesSospechosas(Sospechoso->obtenerRaiz());
    cout << endl;

    // Reiniciar arbol sospechoso
    
    Sospechoso = new arbolAVL();

    Avl->obtenerSospechososPorUbicacion(diferenciaMaximaDeHoras, Sospechoso);
    cout << "=== Transacciones sospechosas por ubicacion ===" << endl;
    Sospechoso->printTransaccionesSospechosas(Sospechoso->obtenerRaiz());

    //Borrar arbol sospechoso
    delete Sospechoso;

}

void eliminarTransa(arbolAVL*& avl) {
    string ID;
    cout << "Indique el ID de la transaccion a eliminar: ";
    cin >> ID;

    if (avl->eliminar(ID)) {
        cout << "Se ha borrado la transaccion con exito." << endl;
        eliminarLineaTXT(ID);
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
    cout << "Ingrese nuevo Nombre de cuenta de origen (actual: " << transaAModificar->transa->getCuentaOrigen() << "): ";
    cin >> nuevaCuentaOrigen;

    string nuevaCuentaDestino;
    cout << "Ingrese nuevo Nombre de cuenta de destino (actual: " << transaAModificar->transa->getCuentaDestino() << "): ";
    cin >> nuevaCuentaDestino;

    double nuevoMonto;
    cout << "Ingrese nuevo monto de la transaccion (actual: " << transaAModificar->transa->getMonto() << "): ";
    cin >> nuevoMonto;

    string nuevaFechaHora;
    cout << "Ingrese nueva fecha y hora (actual: " << transaAModificar->transa->getFechaHora() << "): ";
    cin >> nuevaFechaHora;

    string nuevoLugar;
    cout << "Ingrese nueva Ubicacion(Ciudad/Pais) (actual: " << transaAModificar->transa->getLugar() << "): ";
    cin >> nuevoLugar;

    transaAModificar->transa->setCuentaOrigen(nuevaCuentaOrigen);
    transaAModificar->transa->setCuentaDestino(nuevaCuentaDestino);
    transaAModificar->transa->setMonto(nuevoMonto);
    transaAModificar->transa->setFechaHora(nuevaFechaHora);
    transaAModificar->transa->setLugar(nuevoLugar);
    cout << "Transaccion con ID " << idTransaccion << " modificada exitosamente." << endl;
    //modificar el txt
    //Buscar anteriro
    //Borrar el anterior
    //poner nuevo
    string nuevaLinea = idTransaccion + "," + nuevaCuentaOrigen + "," + nuevaCuentaDestino + "," + to_string(nuevoMonto) + "," + nuevaFechaHora + "," + nuevoLugar;
    modificarLineaTXT("/workspaces/TallerEstructura3/src/data/listadoTransacciones.txt", idTransaccion, nuevaLinea);




}
void modificarLineaTXT(const string& nombreArchivo, const string& idTransaccion, const string& nuevaLinea) {
    ifstream archivoOriginal(nombreArchivo);
    ofstream archivoTemporal(nombreArchivo + ".temp");

    string linea;
    bool esPrimeraLinea = true;

    while (getline(archivoOriginal, linea)) {
        if (linea.substr(0, 3) == idTransaccion) {
            if (!nuevaLinea.empty()) {
                if (!esPrimeraLinea) {
                    archivoTemporal << endl;
                }
                archivoTemporal << nuevaLinea;
                esPrimeraLinea = false;
            }
        } else {
            if (!esPrimeraLinea) {
                archivoTemporal << endl;
            }
            archivoTemporal << linea;
            esPrimeraLinea = false;
        }
    }

    archivoOriginal.close();
    archivoTemporal.close();

    remove(nombreArchivo.c_str());
    rename((nombreArchivo + ".temp").c_str(), nombreArchivo.c_str());
}


void eliminarLineaTXT(string ID){
    // Modificar el txt
    string arch = "/workspaces/TallerEstructura3/src/data/listadoTransacciones.txt";
    string temporal = "/workspaces/TallerEstructura3/src/data/tempListadoTransacciones.txt";
    ifstream archivoOriginal(arch);
    ofstream archivoTemporal(temporal);

    string linea;
    bool esPrimeraLinea = true;
    while (getline(archivoOriginal, linea)) {
        if (linea.substr(0, 3) != ID) {
            if (!esPrimeraLinea) {
                archivoTemporal << endl;
            }
            archivoTemporal << linea;
            esPrimeraLinea = false;
        }
    }

    archivoOriginal.close();
    archivoTemporal.close();

    // Borrar el archivo original y renombrar el temporal
    remove("/workspaces/TallerEstructura3/src/data/listadoTransacciones.txt");
    rename("/workspaces/TallerEstructura3/src/data/tempListadoTransacciones.txt", "/workspaces/TallerEstructura3/src/data/listadoTransacciones.txt");
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
    ifstream archivo("/workspaces/TallerEstructura3/src/data/listadoTransacciones.txt");
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

    string lugar;
    cout << "Ingrese Ubicacion(Ciudad/Pais): ";
    cin >> lugar;

    transaccion* nuevaTransa = new transaccion(nuevoID, cuenta_origen, cuenta_destino, monto, fecha_hora, lugar);
    avl->insertar(nuevaTransa);
    guardarTransaccionEnArchivo("/workspaces/TallerEstructura3/src/data/listadoTransacciones.txt", nuevaTransa);

    cout << "Transaccion agregada exitosamente con ID: " << nuevoID << endl;
}

void cargarTransaccionesDesdeArchivo(arbolAVL*& avl, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de transacciones." << endl;
        return;
    }

    string linea, id, cuentaOrigen, cuentaDestino, fechaHora,lugar;
    double monto;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, id, ',');
        getline(ss, cuentaOrigen, ',');
        getline(ss, cuentaDestino, ',');
        ss >> monto;
        ss.ignore(1, ',');
        getline(ss, fechaHora, ',');
        getline(ss,lugar);
        transaccion* transa = new transaccion(id, cuentaOrigen, cuentaDestino, monto, fechaHora,lugar);
        avl->insertar(transa);
    }

    archivo.close();
}
void guardarTransaccionEnArchivo(const string& nombreArchivo, transaccion* nuevaTransa) {
    ifstream archivo(nombreArchivo);
    bool archivoVacio = archivo.peek() == ifstream::traits_type::eof();
    archivo.close();

    ofstream archivoOut(nombreArchivo, ios::app);
    if (!archivoOut.is_open()) {
        cerr << "Error al abrir el archivo de transacciones." << endl;
        return;
    }

    if (!archivoVacio) {
        archivoOut << endl;
    }
    archivoOut << nuevaTransa->getID() << ','
               << nuevaTransa->getCuentaOrigen() << ','
               << nuevaTransa->getCuentaDestino() << ','
               << nuevaTransa->getMonto() << ','
               << nuevaTransa->getFechaHora() << ','
               << nuevaTransa->getLugar();

    archivoOut.close();
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
