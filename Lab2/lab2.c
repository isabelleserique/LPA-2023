#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pessoa {
    char nome[51];
    long long int cpf;
    int idade;
    struct Pessoa *next;
} Pessoa;

typedef struct ListaPessoas {
    Pessoa *inicio;
} ListaPessoas;

typedef ListaPessoas** TabelaHash;

TabelaHash tabela_hash_pessoas_criar(int tamanho) {
    TabelaHash tabela = (TabelaHash)malloc(sizeof(ListaPessoas*) * tamanho);
    for (int i = 0; i < tamanho; i++) {
        tabela[i] = (ListaPessoas*)malloc(sizeof(ListaPessoas));
        tabela[i]->inicio = NULL;
    }
    return tabela;
}

int tabela_hash_pessoas_funcao(long long int cpf, int tamanho) {
    return (int)(cpf % tamanho);
}

void tabela_hash_pessoas_adicionar(Pessoa *pessoa, TabelaHash tabela_hash, int tamanho) {
    int index = tabela_hash_pessoas_funcao(pessoa->cpf, tamanho);
    pessoa->next = tabela_hash[index]->inicio;
    tabela_hash[index]->inicio = pessoa;
}

void tabela_hash_pessoas_listar(TabelaHash tabela_hash, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("POSIÇÃO %d DA TABELA HASH:\n", i);
        Pessoa *p = tabela_hash[i]->inicio;
        while (p != NULL) {
            printf("- %s\t%lld\t%d\n", p->nome, p->cpf, p->idade);
            p = p->next;
        }
        printf("\n");
    }
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <tamanho_tabela> <arquivo_entrada>\n", argv[0]);
        return 1;
    }

    int tamanho_tabela;
    if (sscanf(argv[1], "%d", &tamanho_tabela) != 1 || tamanho_tabela <= 0) {
        fprintf(stderr, "Tamanho da tabela inválido\n");
        return 1;
    }

    TabelaHash tabela_hash = tabela_hash_pessoas_criar(tamanho_tabela);

    FILE *arq_in = fopen(argv[2], "r");
    if (arq_in == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo de entrada\n");
        return 1;
    }

    Pessoa *p = (Pessoa*)malloc(sizeof(Pessoa));
    while (fscanf(arq_in, "%50[^\t]\t%lld\t%d\n", p->nome, &p->cpf, &p->idade) == 3) {
        tabela_hash_pessoas_adicionar(p, tabela_hash, tamanho_tabela);
        p = (Pessoa*)malloc(sizeof(Pessoa));
    }
    fclose(arq_in);

    tabela_hash_pessoas_listar(tabela_hash, tamanho_tabela);

    //liberar memo
    for (int i = 0; i < tamanho_tabela; i++) {
        free(tabela_hash[i]);
    }
    free(tabela_hash);
    free(p);

    return 0;
}
