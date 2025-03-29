#include <iostream>
using namespace std;


struct nodo {
    int id;
    char nombre[30];
    int edad;
    char genero;
    char motivo[30];
    
    struct nodo *sig;
};

struct nodo *cab = NULL, *aux = NULL, *aux2 = NULL;
int contadorid = 1;


void addcliente() {
    // Se reserva memoria para un nuevo nodo
    aux = (struct nodo *) malloc(sizeof(struct nodo));

    // Se verifica si la memoria fue asignada correctamente
    if (aux == NULL) {
        cout << "Error: no se pudo asignar memoria." << endl;
        return;
    }

    // Solicita al usuario los datos del cliente a guardar
    cout << "Ingrese el nombre: ";
    cin >> aux->nombre;
    cout << "ingrese la edad: ";
    cin >> aux->edad;
    cout << "ingrese el genero (M/F): ";
    cin >> aux->genero;
    cout << "ingrese el motivo de atencion: ";
    cin >> aux->motivo;

    // El acumulador para los id
    aux->id = contadorid++;
    // El nuevo nodo apunta a NULL (fin de lista)
    aux->sig = NULL;
    
    // Si la lista está vacía, el nuevo nodo será la cabeza
    if (cab == NULL) {
        cab = aux;
    } else {
        // Se recorre la lista hasta el último nodo
        aux2 = cab;
        while (aux2->sig != NULL) {
            aux2 = aux2->sig;
        }
        // Se enlaza el nuevo nodo al final
        aux2->sig = aux;
    }
    aux =  aux2 = NULL; // Se limpian los punteros auxiliares
    free(aux);          // Se libera la memoria de aux
    free(aux2);         // Se libera la memoria de aux2
}




void callcliente() {
    cout << "aun no hay nada xd";
};


void viewhistorial() {
    cout << "aun no hay nada xd";
};


void eliminaratencion() {
    cout << "aun no hay nada xd";
};

void liberarMemoria() {
    aux = cab;
    // Recorre la lista y libera nodo por nodo
    while (aux != NULL) {
        aux2 = aux->sig; // Guarda el siguiente nodo
        free(aux);       // Libera el nodo actual
        aux = aux2;      // Avanza al siguiente
    }
    cab = NULL; // Después de liberar, cabeza queda en NULL
    cout << "Memoria liberada correctamente." << endl;
}

int main() {
    int band, opc;

    do {
        // Muestra menú al usuario
        cout << "\n==== MENÚ ====\n";
        cout << "1. Registrar un cliente\n";
        cout << "2. Mostrar lista de clientes en espera\n";
        cout << "3. Atender a un cliente\n";
        cout << "4. Mostrar el historial de atenciones \n";
        cout << "5. Deshacer la última atención.\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opc;

        switch(opc) {
            case 1:
                addcliente();
                break;
            case 2:
                viewhistorial();
                break;
            case 3:
                callcliente();
                break;
                case 4: 
                viewhistorial();
                break;
            case 5:
                eliminaratencion();
            break;    
        }

    } while(opc != 6);

    // Al salir del programa, se libera la memoria
    liberarMemoria();

    return 0;
}