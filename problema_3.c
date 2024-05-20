#include <stdio.h>
#include <omp.h>

// Método para la multiplicación utilizando sumas
int multiplicar(int a, int b) {
    int resultado = 0;
    #pragma omp parallel for reduction(+:resultado)
    for (int i = 0; i < b; i++) {
        resultado += a;
    }
    return resultado;
}

// Método para la división utilizando restas
int dividir(int a, int b) {
    int resultado = 0;
    int temp = a;
    #pragma omp parallel
    {
        int local_resultado = 0;
        while (temp >= b) {
            temp -= b;
            local_resultado++;
        }
        #pragma omp critical
        {
            resultado += local_resultado;
        }
    }
    return resultado;
}

int main() {
    int a = 5;
    int b = 3;
    int resultado_multiplicacion = multiplicar(a, b);
    int resultado_division = dividir(a, b);

    printf("Multiplicación: %d\n", resultado_multiplicacion);
    printf("División: %d\n", resultado_division);

    return 0;
}
