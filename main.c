#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int info;
    struct nodo *sig;
} nodo;

nodo *head = NULL;

nodo* nuevoNodo(int valor);
int size();
int get(int index);
bool contains(int s);
bool add(int s);
void insertarOrdenado(int x);
bool removeByValue(int s);
bool removeByIndex(int index);
int indexOf(int s);
void mostrar();

int main(void) {
    int opcion, valor, index;

    do {
        printf("\n--Menu--\n");
        printf("1. Agregar elemento\n");
        printf("2. Agregar ordenado\n");
        printf("3. Eliminar elemento por valor\n");
        printf("4. Eliminar elemento por índice\n");
        printf("5. Obtener tamaño de la lista\n");
        printf("6. Obtener valor por índice\n");
        printf("7. Verificar si contiene un valor\n");
        printf("8. Obtener índice de un valor\n");
        printf("9. Mostrar\n");
        printf("0. Salir\n");
        printf(">> ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese el valor a agregar: ");
                scanf("%d", &valor);
                add(valor);
                printf("Valor %d agregado a la lista.\n", valor);
                break;
            case 2:
                printf("Ingrese el valor a agregar: ");
                scanf("%d", &valor);
                insertarOrdenado(valor);
                printf("Valor %d agregado a la lista.\n", valor);
                break;
            case 3:
                printf("Ingrese el valor a eliminar: ");
                scanf("%d", &valor);
                if (removeByValue(valor)) {
                    printf("Valor %d eliminado de la lista.\n", valor);
                } else {
                    printf("Valor %d no encontrado en la lista.\n", valor);
                }
                break;
            case 4:
                printf("Ingrese el índice del valor a eliminar: ");
                scanf("%d", &index);
                if (removeByIndex(index)) {
                    printf("Elemento en el índice %d eliminado.\n", index);
                } else {
                    printf("Índice %d no válido.\n", index);
                }
                break;
            case 5:
                printf("El tamaño de la lista es: %d\n", size());
                break;
            case 6:
                printf("Ingrese el índice del valor a obtener: ");
                scanf("%d", &index);
                valor = get(index);
                if (valor != -1) {
                    printf("El valor en el índice %d es: %d\n", index, valor);
                } else {
                    printf("Índice %d no válido.\n", index);
                }
                break;
            case 7:
                printf("Ingrese el valor a buscar: ");
                scanf("%d", &valor);
                if (contains(valor)) {
                    printf("La lista contiene el valor %d.\n", valor);
                } else {
                    printf("El valor %d no se encuentra en la lista.\n", valor);
                }
                break;
            case 8:
                printf("Ingrese el valor para obtener su índice: ");
                scanf("%d", &valor);
                index = indexOf(valor);
                if (index != -1) {
                    printf("El valor %d se encuentra en el índice %d.\n", valor, index);
                } else {
                    printf("El valor %d no se encuentra en la lista.\n", valor);
                }
                break;
            case 9:
                mostrar();
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 0);
}


nodo* nuevoNodo(int valor) {
    nodo* nuevo = (nodo*)malloc(sizeof(nodo));
    nuevo->info = valor;
    nuevo->sig = NULL;
    return nuevo;
}

int size() {
    if (head == NULL) {
        return 0;
    }

    nodo *element = head;
    int i = 1;

    while (element->sig != NULL) {
        element = element->sig;
        i++;
    }

    return i;
}

int get(int index) {
    if (index < 0 || index >= size()) {
        return -1;
    }

    if (head == NULL) {
        return -1;
    }

    if (index == 0) {
        return head->info;
    }

    nodo *element = head->sig;
    for (int i = 1; i < index; i++) {
        element = element->sig;
    }
    return element->info;
}

bool contains(int s) {
    if (head == NULL) {
        return false;
    }

    if (head->info == s) {
        return true;
    }

    nodo *element = head->sig;

    for (int i = 1; i < size(); i++) {
        if (element->info == s) {
            return true;
        }
        element = element->sig;
    }

    return false;
}

bool add(int s) {
    nodo *next = nuevoNodo(s);

    if (head == NULL) {
        head = next;
    } else {
        nodo *last = head;
        while (last->sig != NULL) {
            last = last->sig;
        }
        last->sig = next;
    }
    return true;
}

bool removeByValue(int s) {
    if (head == NULL) {
        return false;
    }

    if (head->info == s) {
        nodo *temp = head;
        head = head->sig;
        free(temp);
        return true;
    }

    nodo *element = head;
    while (element->sig != NULL && element->sig->info != s) {
        element = element->sig;
    }

    if (element->sig != NULL) {
        nodo *toDelete = element->sig;
        element->sig = element->sig->sig;
        free(toDelete);
        return true;
    }

    return false;
}

bool removeByIndex(int index) {
    if (head == NULL || index < 0 || index >= size()) {
        return false;
    }

    if (index == 0) {
        nodo *temp = head;
        head = head->sig;
        free(temp);
        return true;
    }

    nodo *element = head;
    for (int i = 1; i < index; i++) {
        element = element->sig;
    }

    nodo *toDelete = element->sig;
    element->sig = toDelete->sig;
    free(toDelete);
    return true;
}

int indexOf(int s) {
    if (head == NULL) {
        return -1;
    }

    nodo *element = head;
    int i = 0;

    while (element != NULL && element->info != s) {
        element = element->sig;
        i++;
    }

    if (element == NULL) {
        return -1;
    }

    return i;
}

void mostrar()
{
    nodo *elem = head;
    if (elem == NULL)
    {
        printf("La cola está vacía");
        return;
    }
    while (elem != NULL)
    {
        printf("-%d", elem->info);
        elem = elem->sig;
    }
    printf("-\n");
}

void insertarOrdenado(int x)
{
    nodo *nuevo = malloc(sizeof(nodo));
    nuevo->info = x;
    nuevo->sig = NULL;

    if (head == NULL)
    {
        // Si la lista está vacía, el nuevo nodo se convierte en el primer nodo
        head = nuevo;
    }
    else
    {
        // Si el valor es menor que la cabeza, el nuevo nodo se convierte en la nueva cabeza
        if (x < head->info)
        {
            nuevo->sig = head;
            head = nuevo;
        }
        else
        {
            // Recorremos la lista para encontrar la posición correcta
            nodo *current = head;
            while (current->sig != NULL && current->sig->info < x)
            {
                current = current->sig;
            }
            // Insertamos el nuevo nodo en la posición encontrada
            nuevo->sig = current->sig;
            current->sig = nuevo;
        }
    }
}

