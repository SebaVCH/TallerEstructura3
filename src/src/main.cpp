#include <iostream>

using namespace std;

//Menu
void mostrarMenu();

//Cargar y guardar datos

//Funciones a utilizar


int main() {
    mostrarMenu();
    return 0;
}

void mostrarMenu() {
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
