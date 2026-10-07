// Arquivo TabelaHash.c

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "TabelaHash.h" // Inclui os protótipos

// Definição do tipo Hash
struct hash {
    int qtd;
    int TABLE_SIZE;
    struct aluno **itens;
};


// Cria a tabela hash
Hash* criaHash(int TABLE_SIZE) {

    // Tamanho inválido
    if (TABLE_SIZE <= 0)
        return NULL;

    Hash* ha = (Hash*) malloc(sizeof(Hash));

    if (ha != NULL) {

        int i;

        ha->TABLE_SIZE = TABLE_SIZE;
        ha->qtd = 0;

        // Aloca o vetor de ponteiros para alunos
        ha->itens = (struct aluno**) malloc(
            TABLE_SIZE * sizeof(struct aluno*)
        );

        if (ha->itens == NULL) {
            free(ha);
            return NULL;
        }

        // Inicializa todas as posições com NULL
        for (i = 0; i < ha->TABLE_SIZE; i++)
            ha->itens[i] = NULL;
    }

    return ha;
}


// Libera a tabela hash
void liberaHash(Hash* ha) {

    if (ha != NULL) {

        int i;

        for (i = 0; i < ha->TABLE_SIZE; i++) {

            if (ha->itens[i] != NULL)
                free(ha->itens[i]);
        }

        free(ha->itens);
        free(ha);
    }
}


// Função hash pelo método da divisão
int chaveDivisao(int chave, int TABLE_SIZE) {

    return (chave & 0x7FFFFFFF) % TABLE_SIZE;
}


// Insere um elemento na tabela hash
// Esta versão NÃO trata colisões
int insereHash_SemColisao(Hash* ha, struct aluno al) {

    // Verifica se a tabela existe
    // e se ainda há espaço
    if (ha == NULL || ha->qtd == ha->TABLE_SIZE)
        return 0;

    int chave = al.matricula;

    // Caso a chave seja uma string, poderia ser utilizada:
    // int chave = valorString(al.nome);

    int pos = chaveDivisao(chave, ha->TABLE_SIZE);

    // Como esta implementação não trata colisões,
    // a posição precisa estar livre.
    if (ha->itens[pos] != NULL)
        return 0;

    struct aluno* novo;

    novo = (struct aluno*) malloc(sizeof(struct aluno));

    if (novo == NULL)
        return 0;

    // Copia os dados do aluno
    *novo = al;

    // Insere o aluno na posição calculada
    ha->itens[pos] = novo;

    ha->qtd++;

    return 1;
}


// Busca um aluno pela matrícula
int buscaHash_SemColisao(Hash* ha, int mat, struct aluno* al) {

    if (ha == NULL || al == NULL)
        return 0;

    int pos = chaveDivisao(mat, ha->TABLE_SIZE);

    // Não existe elemento nessa posição
    if (ha->itens[pos] == NULL)
        return 0;

    // Como a tabela não trata colisões,
    // é importante verificar a matrícula.
    if (ha->itens[pos]->matricula != mat)
        return 0;

    // Copia o aluno encontrado
    *al = *(ha->itens[pos]);

    return 1;
}

// Imprime o código hash de cada aluno
void imprimeHash(Hash* ha) {

    if (ha == NULL) {
        printf("Tabela hash invalida!\n");
        return;
    }

    printf("\n========================================\n");
    printf("        CODIGO HASH DOS ALUNOS\n");
    printf("========================================\n");

    for (int i = 0; i < ha->TABLE_SIZE; i++) {

        if (ha->itens[i] != NULL) {

            int matricula = ha->itens[i]->matricula;

            int hash = chaveDivisao(
                matricula,
                ha->TABLE_SIZE
            );

            printf("Nome: %-15s | "
                   "Matricula: %4d | "
                   "Hash: %2d | "
                   "Posicao: %2d\n",
                   ha->itens[i]->nome,
                   matricula,
                   hash,
                   i);
        }
    }

    printf("========================================\n");
}