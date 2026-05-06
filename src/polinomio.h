#ifndef POLINOMIO_H
#define POLINOMIO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Termino{
    float coeficiente;
    int exponente;
}Term;

typedef struct Nodo{
    Term termino;
    struct Nodo* next;
    struct Nodo* ant;
}Nodo;

typedef struct{
    Nodo* head;
    Nodo* tail;
    int num_terminos;
}Polinomio;

Nodo* crear_nodo(float coeficiente, int exponente);
Polinomio* polinomio_vacio();
void eliminar_nodo(Polinomio* p, Nodo* n);
void insertar_termino(float coef, int exp, Polinomio* p);
void mostrar_polinomio(Polinomio* p);
float evaluar_polinomio(float x, Polinomio* p);
Polinomio* sumar_polinomios(Polinomio* p1, Polinomio* p2);
Polinomio* multiplicar_polinomios(Polinomio* p1, Polinomio* p2);

Nodo* crear_nodo(float coeficiente, int exponente){
    Nodo* new_node = (Nodo*)malloc(sizeof(Nodo));
    new_node->termino.coeficiente = coeficiente;
    new_node->termino.exponente = exponente;
    new_node->next = new_node->ant = NULL;
    return new_node;
}

Polinomio* polinomio_vacio(){
    Polinomio* p = (Polinomio*)malloc(sizeof(Polinomio));
    p->head = p->tail = NULL;
    p->num_terminos = 0;
    return p;
}

void eliminar_nodo(Polinomio* p, Nodo* n){
    if (n == NULL) return;
    if (n->ant) n->ant->next = n->next;
    else p->head = n->next;

    if (n->next) n->next->ant = n->ant;
    else p->tail = n->ant;

    free(n);
    p->num_terminos--;
}

void insertar_termino(float coef, int exp, Polinomio* p){
    if (coef == 0) return;

    Nodo* actual = p->head;

    while(actual != NULL && actual->termino.exponente > exp){
        actual = actual->next;
    }

    if(actual != NULL && actual->termino.exponente == exp){
        actual->termino.coeficiente += coef;
        if(actual->termino.coeficiente == 0){
            eliminar_nodo(p, actual);
        }
        return;
    }

    Nodo* nuevo = crear_nodo(coef, exp);
    if(p->head == NULL){
        p->head = p->tail = nuevo;
    }else if(actual == p->head){
        nuevo->next = p->head;
        p->head->ant = nuevo;
        p->head = nuevo;
    }else if(actual == NULL){
        nuevo->ant = p->tail;
        p->tail->next = nuevo;
        p->tail = nuevo;
    }else{
        nuevo->next = actual;
        nuevo->ant = actual->ant;
        actual->ant->next = nuevo;
        actual->ant = nuevo;
    }
    p->num_terminos++;
}

void mostrar_polinomio(Polinomio* p){
    if(p->head == NULL){
        printf("0\n");
        return;
    }
    Nodo* tmp = p->head;
    while(tmp != NULL){
        if(tmp != p->head && tmp->termino.coeficiente > 0) printf("+");
        printf("%.0fx^%d", tmp->termino.coeficiente, tmp->termino.exponente);
        tmp = tmp->next;
    }
    printf("\n");
}

float evaluar_polinomio(float x, Polinomio* p){
    float resultado = 0;
    Nodo* tmp = p->head;
    while(tmp != NULL){
        resultado += tmp->termino.coeficiente * pow(x, tmp->termino.exponente);
        tmp = tmp->next;
    }
    return resultado;
}

Polinomio* sumar_polinomios(Polinomio* p1, Polinomio* p2){
    Polinomio* res = polinomio_vacio();
    Nodo* t1 = p1->head;
    while(t1 != NULL){
        insertar_termino(t1->termino.coeficiente, t1->termino.exponente, res);
        t1 = t1->next;
    }
    Nodo* t2 = p2->head;
    while(t2 != NULL){
        insertar_termino(t2->termino.coeficiente, t2->termino.exponente, res);
        t2 = t2->next;
    }
    return res;
}

Polinomio* multiplicar_polinomios(Polinomio* p1, Polinomio* p2){
    Polinomio* res = polinomio_vacio();
    for(Nodo* n1 = p1->head; n1 != NULL; n1 = n1->next){
        for(Nodo* n2 = p2->head; n2 != NULL; n2 = n2->next){
            float c = n1->termino.coeficiente * n2->termino.coeficiente;
            int e = n1->termino.exponente + n2->termino.exponente;
            insertar_termino(c, e, res);
        }
    }
    return res;
}

#endif
