#include <iostream>
using namespace std;

struct nodo {
    int id;
    char nombre[30];
    int edad;
    char genero;
    char motivo[50];
    struct nodo *sig;
};

struct nodo *cab = NULL, *aux = NULL, *aux2 = NULL;
struct nodo *historial = NULL; // Pila para el historial
int contadorid = 1;

void addcliente() {
    aux = (struct nodo *)malloc(sizeof(struct nodo));
    if (aux == NULL) {
        cout << "Error: no se pudo asignar memoria." << endl;
        return;
    }
    cin.ignore();
    cout << "Ingrese el nombre: ";
    cin.getline(aux->nombre, 30);
    cout << "Ingrese la edad: ";
    cin >> aux->edad;
    if (aux->edad < 18) {
        cout << "Acceso denegado. Debes ser mayor de edad." << endl;
        free(aux);
        return;
    }
    cout << "Ingrese el género (M/F): ";
    cin >> aux->genero;
    cin.ignore();
    cout << "Ingrese el motivo de atención: ";
    cin.getline(aux->motivo, 50);
    aux->id = contadorid++;
    aux->sig = NULL;
    if (cab == NULL) {
        cab = aux;
    } else {
        aux2 = cab;
        while (aux2->sig != NULL) {
            aux2 = aux2->sig;
        }
        aux2->sig = aux;
    }
}

int contarClientesEnEspera() {
    int contador = 0;
    for (aux = cab; aux != NULL; aux = aux->sig) {
        contador++;
    }
    return contador;
}

void viewespera() {
    for (aux = cab; aux != NULL; aux = aux->sig) {
        cout << "Clientes en espera: " << aux->nombre << " ID: " << aux->id << endl;
    }
    cout << "Cantidad de clientes en espera: " << contarClientesEnEspera() << endl;
}

void agregarAlHistorial(nodo *cliente) {
    nodo *nuevo = (nodo *)malloc(sizeof(nodo));
    if (nuevo == NULL) {
        cout << "Error: no se pudo asignar memoria para historial." << endl;
        return;
    }
    *nuevo = *cliente;
    nuevo->sig = historial;
    historial = nuevo;
}

void atendercliente() {
    if (cab == NULL) {
        cout << "No hay clientes en espera." << endl;
        return;
    }

    // Guardar referencia del primer cliente en aux2
    aux2 = cab;

    // Mover la cabeza al siguiente cliente en la cola
    cab = cab->sig;

    // Mostrar al cliente que se está atendiendo
    cout << "Atendiendo a: " << aux2->nombre << " (ID: " << aux2->id << ") - Motivo: " << aux2->motivo << endl;

    // Agregar al historial antes de eliminar
    agregarAlHistorial(aux2);

    // Liberar la memoria del cliente atendido
    free(aux2);
}

void viewhistorial() {
    if (historial == NULL) {
        cout << "No hay atenciones en el historial." << endl;
        return;
    }
    cout << "\nHistorial de atenciones:" << endl;
    for (aux = historial; aux != NULL; aux = aux->sig) {
        cout << "ID: " << aux->id << " - Nombre: " << aux->nombre << " - Motivo: " << aux->motivo << endl;
    }
}

void eliminaratencion() {
    if (historial == NULL) {
        cout << "No hay atenciones para deshacer." << endl;
        return;
    }
    nodo *ultimo = historial;
    historial = historial->sig;
    ultimo->sig = cab;
    cab = ultimo;
    cout << "Se ha deshecho la última atención. Cliente " 
         << ultimo->nombre << " regresado a la lista de espera." << endl;
}

void liberarMemoria() {
    aux = cab;
    while (aux != NULL) {
        aux2 = aux->sig;
        free(aux);
        aux = aux2;
    }
    cab = NULL;
    aux = historial;
    while (aux != NULL) {
        aux2 = aux->sig;
        free(aux);
        aux = aux2;
    }
    historial = NULL;
    cout << "Memoria liberada correctamente." << endl;
}

int main() {
    int opc;
    do {
        cout << "\n==== MENÚ ====" << endl;
        cout << "1. Registrar un cliente en espera" << endl;
        cout << "2. Mostrar lista de clientes en espera" << endl;
        cout << "3. Atender cliente (LIFO)" << endl;
        cout << "4. Mostrar el historial de atenciones" << endl;
        cout << "5. Deshacer la última atención" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opc;
        switch (opc) {
            case 1:
                addcliente();
                break;
            case 2:
                viewespera();
                break;
            case 3:
                atendercliente();
                break;
            case 4:
                viewhistorial();
                break;
            case 5:
                eliminaratencion();
                break;
        }
    } while (opc != 6);
    liberarMemoria();
    return 0;
}