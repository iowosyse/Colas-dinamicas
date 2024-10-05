#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int info;
    struct nodo *sig;
} nodo;

nodo *head = NULL;

void menu();
void meter();
int sacar();
void mostrar();

void main()
{
    menu();
}

void menu()
{
    int opt;

    do
    {
        printf("1. Meter\n2. Sacar\n3. Mostrar\n0. Salir\n>> ");
        scanf("%d", &opt);

        switch (opt)
        {
            case 1:
                meter();
                break;
            case 2:
                sacar();
                break;
            case 0:
                printf("...");
                break;
            case 3:
                mostrar();
                break;
            default:
                printf("No se vale");
                break;
        }

    } while (opt != 0);
}

void meter()
{
    int input;
    printf("Ingrese el número que entra a la cola: \n>>");
    scanf("%d", &input);

    nodo *nuevo = malloc(sizeof(nodo));

    nuevo->info = input;
    nuevo->sig = NULL;

    if (head == NULL)
    {
        head = nuevo;
    }
    else
    {
        nodo *elem = head;
        while (elem->sig != NULL)
            elem = elem->sig;

        elem->sig = nuevo;
    }
}

int sacar()
{
    int data = -1;

    if (head == NULL)
        return data;

    if (head->sig != NULL)
    {
        nodo *elem = head;
        head = head->sig;
        data = elem->info;
        free(elem);
    }
    else
    {
        data = head->info;
        head = NULL;
    }

    return data;
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
