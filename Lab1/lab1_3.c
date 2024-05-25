#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct lista_eventos lista_eventos_t;

//armazenamento de evento
typedef struct evento {
    double tempo;
    int alvo;
    int tipo;
} evento_t;

//estrutur lista_eventos_t
struct lista_eventos {
    evento_t* evento;
    struct lista_eventos* next;
};

//Função para adicionar um evento em ordem
bool lista_eventos_adicionar_ordenado(evento_t *evento, lista_eventos_t **lista) {
    if (evento == NULL) {
        return false; //nulo = não pode ser adicionado à lista
    }

    lista_eventos_t *item_novo = malloc(sizeof(lista_eventos_t));
    if (item_novo == NULL) {
        return false; // nulo = não pode alocar memória no novo nó
    }

    item_novo->evento = evento;
    item_novo->next = NULL;

    //lista vazia = insere inicio lista
    if (*lista == NULL || evento->tempo < (*lista)->evento->tempo) {
        item_novo->next = *lista;
        *lista = item_novo;
        return true;
    }

    //percorre lista
    lista_eventos_t **att = lista;
    while (*att != NULL && (*att)->evento->tempo < evento->tempo) {
        att = &(*att)->next;
    }

    item_novo->next = *att;
    *att = item_novo;

    return true;
}

void lista_eventos_listar(lista_eventos_t* lista) {
    lista_eventos_t* att = lista;

    printf("eventos:\n");
    while (att != NULL) {
        printf("Tempo: %3.6f, Alvo: %d, Tipo: %d\n",
               att->evento->tempo, att->evento->alvo, att->evento->tipo);
        att = att->next;
    }
}

void leitura(const char *arqtxt, lista_eventos_t **lista) {
    double tempo;
    int alvo, tipo;

    FILE *arquivo = fopen(arqtxt, "r");
    if (arquivo == NULL) {
        return;
    }

    while (fscanf(arquivo, "%lf\t%d\t%d\n", &tempo, &alvo, &tipo) == 3) {
        evento_t *newevent = malloc(sizeof(evento_t));
        if (newevent == NULL) {
            fclose(arquivo);
            return;
        }

        newevent->tempo = tempo;
        newevent->alvo = alvo;
        newevent->tipo = tipo;

        if (!lista_eventos_adicionar_ordenado(newevent, lista)) {
            fclose(arquivo);
            return;
        }
    }

    fclose(arquivo);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("insira arquivo: %s\n", argv[0]);
        return 1;
    }

    lista_eventos_t* lista = NULL;
    leitura(argv[1], &lista);
    lista_eventos_listar(lista);

    lista_eventos_t *att = lista;
    while (att != NULL) {
        lista_eventos_t *next = att->next;
        free(att->evento);
        free(att);
        att = next;
    }

    return 0;
}
