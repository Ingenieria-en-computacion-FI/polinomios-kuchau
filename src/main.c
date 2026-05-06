#include <stdio.h>
#include "polinomio.h"

int main() {
    Polinomio* p1 = polinomio_vacio();
    insertar_termino(3, 2, p1);
    insertar_termino(2, 1, p1);
    insertar_termino(1, 0, p1);

    Polinomio* p2 = polinomio_vacio();
    insertar_termino(1, 2, p2);
    insertar_termino(4, 0, p2);

    printf("P1: "); 
    mostrar_polinomio(p1);
    
    printf("P2: "); 
    mostrar_polinomio(p2);

    Polinomio* suma = sumar_polinomios(p1, p2);
    printf("Suma (P1 + P2): "); 
    mostrar_polinomio(suma);

    float x = 2.0;
    printf("Evaluacion de P1 en x=%.1f: %.2f\n", x, evaluar_polinomio(x, p1));

    Polinomio* mult = multiplicar_polinomios(p1, p2);
    printf("Multiplicacion (P1 * P2): ");
    mostrar_polinomio(mult);

    return 0;
}
