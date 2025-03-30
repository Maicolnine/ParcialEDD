//Michael Stwar Murillo Ruiz y Cesar Alberto Grain Agudelo

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

struct nodo *historial = NULL;
struct nodo *cab = NULL, *aux = NULL, *aux2 = NULL;
int contadorid = 1;

void addcliente() {
    int hombres = 0, mujeres = 0;
    for (aux2 = cab; aux2 != NULL; aux2 = aux2->sig) {
        if (aux2->genero == 'M' || aux2->genero == 'm') hombres++;
        else if (aux2->genero == 'F' || aux2->genero == 'f') mujeres++;
    }

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
    if ((aux->genero == 'M' || aux->genero == 'm') && (hombres - mujeres >= 4) ||
        (aux->genero == 'F' || aux->genero == 'f') && (mujeres - hombres >= 4)) {
        cout << "Diferencia de género excedida." << endl;
        free(aux);
        return;
    }
    cin.ignore();
    cout << "Ingrese el motivo de atención: ";
    cin.getline(aux->motivo, 50);
    aux->id = contadorid++;
    aux->sig = NULL;
    if (cab == NULL) cab = aux;
    else {
        aux2 = cab;
        while (aux2->sig != NULL) aux2 = aux2->sig;
        aux2->sig = aux;
    }
}

void viewhistorial(nodo *cliente) {
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

    // Guardar referencia del primer cliente
    aux2 = cab;

    // Mover la cabeza de la cola al siguiente cliente
    cab = cab->sig;

    // Agregar al historial antes de eliminar
    viewhistorial(aux2);

    // Mostrar quién está siendo atendido
    cout << "Atendiendo a: " << aux2->nombre << " (ID: " << aux2->id << ")" << endl;

    // Liberar la memoria del cliente atendido
    free(aux2);
}

void viewespera() {
    int contador = 0;
    for (aux = cab; aux != NULL; aux = aux->sig, contador++)
        cout << "Cliente en espera: " << aux->nombre << " ID: " << aux->id << endl;
    cout << "Total de clientes en espera: " << contador << endl;
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
    cout << "Última atención deshecha. Cliente " << ultimo->nombre << " regresado a la lista." << endl;
}

void liberarMemoria() {
    while (cab != NULL) {
        aux = cab;
        cab = cab->sig;
        free(aux);
    }
    while (historial != NULL) {
        aux = historial;
        historial = historial->sig;
        free(aux);
    }
    cout << "Memoria liberada." << endl;
}

int main() {
    int opc;
    do {
        cout << "\n==== MENÚ ====\n";
        cout << "1. Registrar un cliente\n";
        cout << "2. Atender a un cliente\n";
        cout << "3. Mostrar clientes en espera\n";
        cout << "4. Mostrar historial de atenciones\n";
        cout << "5. Deshacer la última atención\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opc;

        switch (opc) {
            case 1: addcliente(); break;
            case 2: atendercliente(); break;
            case 3: viewespera(); break;
            case 4:
                if (historial == NULL) cout << "No hay clientes en el historial." << endl;
                else {
                    cout << "Historial de atenciones:\n";
                    for (aux = historial; aux != NULL; aux = aux->sig)
                        cout << "Cliente: " << aux->nombre << " (ID: " << aux->id << ")\n";
                }
                break;
            case 5: eliminaratencion(); break;
        }
    } while (opc != 6);
    liberarMemoria();
    return 0;
}
