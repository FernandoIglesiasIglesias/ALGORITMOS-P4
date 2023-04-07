/*
AUTORES:
- Fernando Iglesias Iglesias - login: f.iglesias2
- Anxo Gallego Mato          - login: anxo.gallego
- Luís López García          - login: luis.lopez
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#define TAM 512000

typedef struct {
    int vector[TAM];
    int ultimo;
} monticulo;

void crear_monticulo(int v[], int tam, monticulo* M);
int eliminar_mayor(monticulo* M);
void ord_monticulo(int v[], int tam);
void hundir(monticulo* M, int i);
int es_monticulo_vacio(monticulo M);
void mostrar_monticulo(monticulo M);
void mostrar_vector(int v[], int lenght);
void vector_ascendente(int v[], int tam);
void vector_descendente(int v[], int tam);
void vector_aleatorio(int v[], int tam);
void test();
void test_ord();
void comprobar_complejidad_lineal();
void calc_tiempos_ord(void (*tipovector)(int[], int));
void mostar_tablas();
double microsegundos();
void inicializar_semilla();

int main() {
    inicializar_semilla();
    test();
    comprobar_complejidad_lineal();
    mostar_tablas();
    return 0;
}

void test() {
    int v[]={5,4,3,5,7,8,5,9,8,15,12,13}; int tam = 12; monticulo M;
    printf("----- TEST FUNCIONES -----\n");
    printf("\nCreamos un monticulo con el siguiente vector:\n");
    mostrar_vector(v,tam);
    crear_monticulo(v,tam,&M);
    printf("Quedando el siguiente monticulo: \n");
    mostrar_monticulo(M);
    printf("Eliminamos el elemento mayor, quedando el siguiente monticulo:");
    printf("\n");
    eliminar_mayor(&M);
    mostrar_monticulo(M);
    test_ord();
}

void test_ord() {
    int v[TAM];
    printf("\nComprobamos el funcionamiento de ordenacion por monticulos:\n");
    vector_aleatorio(v,15);
    printf("Vector generado aleatoriamente (sin ordenar) de 15 elementos:\n");
    mostrar_vector(v,15);
    ord_monticulo(v,15);
    printf("Vector ordenado:\n");
    mostrar_vector(v,15);
}
double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}
void inicializar_semilla() {
    srand(time(NULL));
}

void comprobar_complejidad_lineal() {
    double t,ta,tb,x,y,z; int v[TAM], i, n; monticulo M;
    printf("\n");
    printf("Tabla para demostrar la complejidad de crear monticulo O(n):\n");
    printf("         n      t(n)      t(n)/f(n)     t(n)/g(n)     t(n)/h(n)");
    printf("\n");
    for (n = 1000; n <= 256000; n=n*2) {
        vector_ascendente(v,n);
        ta = microsegundos();
        crear_monticulo(v,n,&M);
        tb = microsegundos();
        t = tb - ta;
        if (t < 500) {
            ta = microsegundos();
            for (i = 0; i < 1000; i++) {
                crear_monticulo(v,n,&M);
            }
            tb = microsegundos();
            t = (tb - ta)/1000;
            x = t/(pow(n,0.9));
            y = t/n;
            z = t/(pow(n,1.2));
            printf("(*)%7d%10.3f%15.4f%14.4f%14.5f\n",n,t,x,y,z);
        } else {
            x = t/(pow(n,0.9));
            y = t/n;
            z = t/(pow(n,1.2));
            printf("%10d%10.3f%15.4f%14.4f%14.5f\n",n,t,x,y,z);
        }
    }
}

void calc_tiempos_ord(void (*tipovector)(int[], int)) {
    double t,t500,ta,tb,x,y,z; int v[TAM], n, i;
    printf("         n      t(n)      t(n)/f(n)     t(n)/g(n)     t(n)/h(n)");
    printf("\n");
    for (n = 500; n <= 64000; n=n*2) {
        tipovector(v,n);
        ta = microsegundos();
        ord_monticulo(v,n);
        tb = microsegundos();
        t = tb - ta;

        if (t < 500) {
            ta = microsegundos();
            for (i = 0; i < 1000; i++) {
                tipovector(v,n);
                ord_monticulo(v,n);
            }
            tb = microsegundos();
            t = tb - ta;
            ta = microsegundos();
            for (i = 0; i < 1000; i++) {
                tipovector(v,n);
            }
            tb = microsegundos();
            t500 = tb - ta;
            t = (t - t500)/1000;
            x = t/(pow(n,0.92));
            y = t/(n*log(n));
            z = t/(pow(n,1.4));
            printf("(*)%7d%10.3f%15.4f%14.4f%14.5f\n",n,t,x,y,z);
        } else {
            x = t/(pow(n,0.92));
            y = t/(n*log(n));
            z = t/(pow(n,1.4));
            printf("%10d%10.3f%15.4f%14.4f%14.5f\n",n,t,x,y,z);
        }
        
    }
}

void mostar_tablas() {
    printf("Tabla tiempos ordenacion vector ascendente:\n");
    calc_tiempos_ord(vector_ascendente);
    printf("Tabla tiempos ordenacion vector descendente:\n");
    calc_tiempos_ord(vector_descendente);
    printf("Tabla tiempos ordenacion vector generado aleatoriamente:\n");
    calc_tiempos_ord(vector_aleatorio);
}

void vector_ascendente(int v[], int tam) {
    int i;
    for (i = 0; i < tam; i++) {
        v[i] = i+1;
    }
}
void vector_descendente(int v[], int tam) {
    int i;
	for (i=0; i<tam; i++) {
        v[i] = tam-i;
    }
}
void vector_aleatorio(int v[], int tam) {
    int i, m=2*tam+1;
    for (i = 0; i < tam; i++) {
        v[i] = (rand()%m) - tam;
    }
}

void mostrar_vector(int v[], int lenght) {
    int i;
    for (i = 0; i < lenght; i++) {
        printf("%d, ", v[i]);
    }
    printf("\n");
}

void hundir(monticulo* M, int i) {
    int HijoIzq, HijoDer, j, aux;
    do {
        HijoIzq = 2*i+1;
        HijoDer = 2*i+2;
        j = i;
        if (HijoDer <= M->ultimo && M->vector[HijoDer] > M->vector[i])
            i = HijoDer;
        if (HijoIzq <= M->ultimo && M->vector[HijoIzq] > M->vector[i])
            i = HijoIzq;
        //intercambio:
        aux = M->vector[i];
        M->vector[i] =  M->vector[j];
        M->vector[j] = aux;
    } while (j != i);
}

void crear_monticulo(int v[], int tam, monticulo* M) {
    int i;
    for (i = 0; i < tam; i++) {
        M->vector[i] = v[i];
    }
    M->ultimo = tam - 1;
    for (i = (M->ultimo)/2 ; i >= 0; i--) {
        hundir(M,i);
    }
}

int es_monticulo_vacio(monticulo M) {
    return M.ultimo < 0;
}

int eliminar_mayor(monticulo* M) {
    int x;
    if(M->ultimo < 0)
        printf("Error al eliminar el mayor: monticulo vacio\n");
    else {
        x = M->vector[0];
        M->vector[0] = M->vector[M->ultimo];
        M->ultimo = M->ultimo - 1;
        if (M->ultimo > 0){
            hundir(M,0);
        } 
        
    }
    return x;
}

void mostrar_monticulo(monticulo M) {
    int i;
    for (i = 0; i <= M.ultimo; i++) {
        printf("%d, ",M.vector[i]);
    }
    printf("\n");
}

void ord_monticulo(int v[], int tam) {
    monticulo M; int i;
    crear_monticulo(v,tam, &M);
    for (i = tam-1; i >= 0; i--) {
        v[i] = eliminar_mayor(&M);
    }
}