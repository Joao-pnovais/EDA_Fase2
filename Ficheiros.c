#ifndef FICHEIROS_C
#define FICHEIROS_C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <math.h>
#include "Antena.h"
#include "Grafo.h"
#include "Nefasto.h"
#include "Ficheiros.h"
/**
 * @file Ficheiros.c
 * @brief Funções para ler e escrever o grafo em ficheiros.
 * @author João Novais
 * @date 2025-05-18
 * 
 */

#pragma region Ficheiros

/**
 * @brief Lê uma matriz de antenas de um ficheiro de texto e insere no grafo.
 * @param g Ponteiro para o grafo.
 * @param filename Nome do ficheiro de texto.
 * @return true se leu e inseriu com sucesso, false caso contrário.
 */
// Leitura de matriz de antenas (como no enunciado)
bool lerMatrizAntenas(Grafo* g, const char* filename, int* linhas, int* colunas) {
    FILE* file = fopen(filename, "r");
    if (!file) return false;

    char linha[256];
    int max_linha = 0, max_col = 0;

    while (fgets(linha, sizeof(linha), file)) {
        int col_atual;
        for (col_atual = 0; linha[col_atual] != '\0' && linha[col_atual] != '\n'; col_atual++) {
            char c = linha[col_atual];
            if (c != '.' && c != '#') {
                inserirAntena(g, c, max_linha, col_atual);
            }
        }
        if (col_atual > max_col) max_col = col_atual;
        max_linha++;
    
       
    }
    fclose(file);
    if (linhas) *linhas = max_linha;
    if (colunas) *colunas = max_col;
    return true;
}
/**
 * @brief Guarda o grafo num ficheiro binário.
 * @param filename Nome do ficheiro binário.
 * @param g Ponteiro para o grafo.
 * @return true se guardou, false caso contrário.
 */

bool guardarBinario(const char* filename, Grafo* g) {
    FILE* f = fopen(filename, "wb");
    if (!f) return false;

    // Guardar número de antenas
    fwrite(&g->numAntenas, sizeof(int), 1, f);
    VAntena* atual = g->listaAntenas;
    // Guardar dados de cada antena
    for (atual = g->listaAntenas; atual != NULL; atual = atual->proximo) {
        fwrite(&atual->frequencia, sizeof(char), 1, f);
        fwrite(&atual->linha, sizeof(int), 1, f);
        fwrite(&atual->coluna, sizeof(int), 1, f);
    }

    fclose(f);
    return true;
}


/**
 * @brief Lê um grafo de um ficheiro binário.
 * @param filename Nome do ficheiro binário.
 * @param g Ponteiro para o grafo.
 * @return true se leu, false caso contrário.
 */
// Ler do ficheiro binário

bool lerBinario(const char* filename, Grafo* g) {
    FILE* f = fopen(filename, "rb");
    if (!f) {
        return false;
    }

    // Limpa o grafo antes de ler
    while (g->listaAntenas) {
        removerVertice(g, g->listaAntenas->frequencia, g->listaAntenas->linha, g->listaAntenas->coluna);
    }

    int numAntenas = 0;
    fread(&numAntenas, sizeof(int), 1, f);
    printf("Número de antenas no ficheiro: %d\n", numAntenas);

    for (int i = 0; i < numAntenas; i++) {
        char freq;
        int linha, coluna;
        fread(&freq, sizeof(char), 1, f);
        fread(&linha, sizeof(int), 1, f);
        fread(&coluna, sizeof(int), 1, f);
        inserirAntena(g, freq, linha, coluna);
        printf("freq=%c, linha=%d, coluna=%d\n", freq, linha, coluna);
    }

    fclose(f);
    return true;
}




#pragma endregion

#endif