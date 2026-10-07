#include <stdio.h>
#include "TabelaHash.h"

/*
Para compilar:

gcc -Wall -Wextra -std=c11 TabelaHash.c main.c -o teste_hash
*/

int main() {

    // ============================================================
    // 1. CRIAÇÃO DA TABELA HASH
    // ============================================================

    int TABLE_SIZE = 11; //recomenda-se número primo

    Hash* ha = criaHash(TABLE_SIZE);

    if (ha == NULL) {
        printf("Erro ao criar a tabela hash!\n");
        return 1;
    }

    printf("Tabela hash criada com sucesso!\n");
    printf("Tamanho da tabela: %d\n\n", TABLE_SIZE);


    // ============================================================
    // 2. CRIAÇÃO DOS ALUNOS
    // ============================================================

    struct aluno a1 = {
        .matricula = 10,
        .nome = "Joao",
        .n1 = 8.0,
        .n2 = 7.5,
        .n3 = 9.0
    };

    struct aluno a2 = {
        .matricula = 21,
        .nome = "Maria",
        .n1 = 9.0,
        .n2 = 8.5,
        .n3 = 10.0
    };

    struct aluno a3 = {
        .matricula = 35,
        .nome = "Pedro",
        .n1 = 7.0,
        .n2 = 6.5,
        .n3 = 8.0
    };


    // ============================================================
    // 3. INSERÇÃO DOS ALUNOS
    // ============================================================

    printf("=== INSERCAO ===\n");

    if (insereHash_SemColisao(ha, a1))
        printf("Aluno %s inserido com sucesso!\n", a1.nome);
    else
        printf("Erro ao inserir aluno %s!\n", a1.nome);


    if (insereHash_SemColisao(ha, a2))
        printf("Aluno %s inserido com sucesso!\n", a2.nome);
    else
        printf("Erro ao inserir aluno %s!\n", a2.nome);


    if (insereHash_SemColisao(ha, a3))
        printf("Aluno %s inserido com sucesso!\n", a3.nome);
    else
        printf("Erro ao inserir aluno %s!\n", a3.nome);


    // ============================================================
    // 4. TESTE DE COLISAO
    // ============================================================
    //
    // TABLE_SIZE = 10
    //
    // matrícula 10 -> 10 % 10 = 0
    // matrícula 20 -> 20 % 10 = 0
    //
    // Portanto, 10 e 20 geram a mesma posição.
    // ============================================================

    struct aluno a4 = {
        .matricula = 20,
        .nome = "Carlos",
        .n1 = 8.0,
        .n2 = 8.0,
        .n3 = 8.0
    };

    printf("\n=== TESTE DE COLISAO ===\n");

    if (insereHash_SemColisao(ha, a4))
        printf("Aluno %s inserido com sucesso!\n", a4.nome);
    else
        printf("Colisao! Nao foi possivel inserir %s.\n", a4.nome);


    // ============================================================
    // 5. BUSCA DE UM ALUNO
    // ============================================================

    struct aluno alunoEncontrado;

    printf("\n=== BUSCA ===\n");

    if (buscaHash_SemColisao(ha, 21, &alunoEncontrado)) {

        printf("Aluno encontrado!\n");
        printf("Matricula: %d\n", alunoEncontrado.matricula);
        printf("Nome: %s\n", alunoEncontrado.nome);
        printf("Notas: %.1f, %.1f, %.1f\n",
               alunoEncontrado.n1,
               alunoEncontrado.n2,
               alunoEncontrado.n3);

    } else {

        printf("Aluno nao encontrado!\n");
    }


    // ============================================================
    // 6. TESTE DE BUSCA DE MATRÍCULA INEXISTENTE
    // ============================================================

    printf("\n=== BUSCA DE MATRICULA INEXISTENTE ===\n");

    if (buscaHash_SemColisao(ha, 99, &alunoEncontrado)) {

        printf("Aluno encontrado!\n");
        printf("Nome: %s\n", alunoEncontrado.nome);

    } else {

        printf("Aluno com matricula 99 nao encontrado.\n");
    }


    printf("\n=== CODIGOS HASH ===\n");

    imprimeHash(ha);

    // ============================================================
    // 7. LIBERAÇÃO DA MEMÓRIA
    // ============================================================

    liberaHash(ha);

    printf("\nTabela hash liberada com sucesso.\n");

    return 0;
}