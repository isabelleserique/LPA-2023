#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int tam;
double next;

typedef struct no_t{
   int id; 
   double pos_x;
   double pos_y;
}no_t;

typedef struct lista_vizinhos_t{
    no_t *no;
    struct lista_vizinhos_t *vizinhos;
}lista_vizinhos_t;

bool lista_vizinhos_adicionar(no_t* no, lista_vizinhos_t **lista){
    lista_vizinhos_t *aux = (lista_vizinhos_t*)malloc(sizeof(lista_vizinhos_t));

    aux->no = no;
    aux->vizinhos = *lista;
    *lista = aux;
    return true;
}

void lista_vizinhos_imprimir(lista_vizinhos_t *lista){
    if(lista == NULL){
        printf("Nao ha vizinhos");
    }

    while(lista!=NULL) {
        printf("%d ", lista->no->id);
        lista = lista->vizinhos;
    }
    printf("\n");
}

void *grafo_criar(lista_vizinhos_t *grafo[]){
   int i;
   if(grafo != NULL){
       for(i = 0; i < tam; i++){
            grafo[i] = NULL;
       }
   }
}

void grafo_atualizar_vizinhos(int tam, double next, lista_vizinhos_t* grafo[]){
     for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            if (i != j){
                if (sqrt(pow(grafo[i]->no->pos_x - grafo[j]->no->pos_x, 2) + pow(grafo[i]->no->pos_y - grafo[j]->no->pos_y, 2)) < next){
                    lista_vizinhos_adicionar(grafo[i]->no, &grafo[j]->vizinhos);
                }
            }
        }
    }
}

void grafo_imprimir(int tam, lista_vizinhos_t* grafo[]){
    for(int i = 0; i < tam; i++){
        printf("No %d: ", i);
        lista_vizinhos_imprimir(grafo[i]->vizinhos);
    }
}

int main(int argc, char **argv){
FILE *arq;
int i = 0;
int id;
double pos_x;
double pos_y;

    if(argc < 2){
        printf("Erro\n insira tam da tabela e o arq de texto\n");
        return 1; 
    }

    arq = fopen(argv[1],"r");

    fscanf(arq, "%d\t%lf", &tam, &next);

    lista_vizinhos_t* grafo[tam];
    grafo_criar(grafo);     
    

    no_t *no = (no_t*)malloc(sizeof(no_t));

    if (arq == NULL){
        printf("erro para compilar arquivo\n");
    }else{
        while(fscanf(arq, "%d\t%lf\t%lf\n", &no->id, &no->pos_x, &no->pos_y) != EOF){
            lista_vizinhos_adicionar(no, &grafo[i]);
            i++;
            no = (no_t*)malloc(sizeof(no_t));               
        }
        grafo_atualizar_vizinhos(tam, next, grafo);
        grafo_imprimir(tam, grafo);
    }
    fclose(arq);
    return 0;
}