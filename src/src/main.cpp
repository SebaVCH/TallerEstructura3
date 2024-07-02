#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
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
void definirMontoSospechoso(int &maximoOriginal);
void definirLapsoDeTiempoYFrecuencia(int &difEntreTran, int &cantMax);
void definirMaximoDeHoras(int &horasMinimas);
void modificarTXT(string ID);
int stringToInt(string& str);
void separarFechaHora(string& fechaHora, int& dia, int& mes, int& año, int& hora, int& minutos);
int calcularDiferenciaMinutos(string& fechaHora1,string& fechaHora2);
void reporteTransaccionesSospechosas(arbolAVL *&Avl, arbolAVL *&Sospechoso,int maximo, int transacciones, int transferencias, int horas);
void obtenerSospechososMontoMaximo(Nodo *nodo, arbolAVL *&Sospechoso,int montoMaximo);

//Cargado y guardado de archivos
void cargarTransaccionesDesdeArchivo(arbolAVL*& avl, const string& nombreArchivo);
void guardarTransaccionEnArchivo(const string& nombreArchivo, transaccion* nuevaTransa);

int main() {
    arbolAVL* arbolTransacciones = new arbolAVL();
    cargarTransaccionesDesdeArchivo(arbolTransacciones, "D:/Programas/c++ workspace visual/taller3/TallerEstructura3/src/data/listadoTransacciones.txt");
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

void reporteTransaccionesSospechosas(arbolAVL *&Avl, arbolAVL *&Sospechoso,int montoMaximo, int diferenciaEntreTransacciones, int cantMaxDeTransferencias, int diferenciaMaximaDeHoras) {

    obtenerSospechososMontoMaximo(Avl->obtenerRaiz(),Sospechoso, montoMaximo);

}

void obtenerSospechososMontoMaximo(Nodo *nodo, arbolAVL *&Sospechoso,int montoMaximo){

    if (nodo == nullptr) {
        return;
    }

    obtenerSospechososMontoMaximo(nodo->izquierdo, Sospechoso,montoMaximo);

    if (nodo->transa->getMonto() > montoMaximo) {
        Sospechoso->insertar(nodo->transa);
    }

    obtenerSospechososMontoMaximo(nodo->derecho, Sospechoso,montoMaximo);

}


void eliminarTransa(arbolAVL*& avl) {
    string ID;
    cout << "Indique el ID de la transaccion a eliminar: ";
    cin >> ID;

    if (avl->eliminar(ID)) {
        cout << "Se ha borrado la transaccion con exito." << endl;
        modificarTXT(ID);
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




}
void modificarTXT(string ID){
     // Modificar el txt
        string arch= "D:/Programas/c++ workspace visual/taller3/TallerEstructura3/src/data/listadoTransacciones.txt";
        string temporal="D:/Programas/c++ workspace visual/taller3/TallerEstructura3/src/data/tempListadoTransacciones.txt";
        ifstream archivoOriginal(arch);
        ofstream archivoTemporal(temporal);

        string linea;
        while (getline(archivoOriginal, linea)) {
            if (linea.substr(0, 3) != ID) {
                archivoTemporal << linea << endl;
            }
        }

        archivoOriginal.close();
        archivoTemporal.close();

        // Borrar el archivo original y renombrar el temporal
        remove("D:/Programas/c++ workspace visual/taller3/TallerEstructura3/src/data/listadoTransacciones.txt");
        rename("D:/Programas/c++ workspace visual/taller3/TallerEstructura3/src/data/tempListadoTransacciones.txt", "D:/Programas/c++ workspace visual/taller3/TallerEstructura3/src/data/listadoTransacciones.txt");
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

    string lugar;
    cout << "Ingrese Ubicacion(Ciudad/Pais): ";
    cin >> lugar;

    transaccion* nuevaTransa = new transaccion(nuevoID, cuenta_origen, cuenta_destino, monto, fecha_hora, lugar);
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
            << nuevaTransa->getFechaHora() << ','
            << nuevaTransa->getLugar();

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

int stringToInt(string& str) {
    std::stringstream ss(str);
    int num;
    ss >> num;
    return num;
}
void separarFechaHora(string& fechaHora, int& dia, int& mes, int& año, int& hora, int& minutos) {
    string diaStr, mesStr, añoStr, horaStr, minutosStr;

    diaStr = fechaHora.substr(0, 2);
    mesStr = fechaHora.substr(3, 2);
    añoStr = fechaHora.substr(6, 4);
    horaStr = fechaHora.substr(11, 2);
    minutosStr = fechaHora.substr(14, 2);

    dia = stringToInt(diaStr);
    mes = stringToInt(mesStr);
    año = stringToInt(añoStr);
    hora = stringToInt(horaStr);
    minutos = stringToInt(minutosStr);
}
int calcularDiferenciaMinutos(string& fechaHora1,string& fechaHora2) {
    int dia1, mes1, año1, hora1, minutos1;
    int dia2, mes2, año2, hora2, minutos2;

    separarFechaHora(fechaHora1, dia1, mes1, año1, hora1, minutos1);
    separarFechaHora(fechaHora2, dia2, mes2, año2, hora2, minutos2);

    int totalMinutos1 = ((año1 * 365 + mes1 * 30 + dia1) * 24 + hora1) * 60 + minutos1;
    int totalMinutos2 = ((año2 * 365 + mes2 * 30 + dia2) * 24 + hora2) * 60 + minutos2;

    return abs(totalMinutos2 - totalMinutos1);
}