#include <iostream>
#include "../include/arbolAVL.h"


using namespace std;

//Menu
void mostrarMenu(arbolAVL& avl);

//Cargar y guardar datos

//Funciones a utilizar
void agregarNuevaTransa(arbolAVL& avl);

int main() {

    arbolAVL arbolTransacciones;
    mostrarMenu(arbolTransacciones);

    cout << "Hola" << endl;
    return 0;
}

void mostrarMenu(arbolAVL& avl) {
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
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
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

void agregarNuevaTransa(arbolAVL& avl) {


    transaccion* nuevaTransa = new transaccion("001","Juan","Pedro",1000,"08-06-2024 13:34");
    avl.insertar(nuevaTransa);

}
