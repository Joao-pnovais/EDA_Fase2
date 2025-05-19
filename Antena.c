#ifndef ANTENA_C
#define ANTENA_C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <math.h>
#include "Antena.h"
#include "Grafo.h"
#include "Nefasto.h"
#include "Ficheiros.h"
#pragma region Antenas
/** 
 * @file Antena.c
 * @brief Implementação das funções relacionadas às antenas.
 * @author João Novais
 * @date 2025-05-18
 * 
 */
 

/**
 * @brief Cria uma nova antena.
 * @param freq Frequência da antena.
 * @param linha Linha da antena.
 * @param coluna Coluna da antena.
 * @return Ponteiro para a antena criada, ou NULL em caso de erro.
 */

// Criar nova antena
VAntena* criarAntena(char freq, int linha, int coluna) {
    VAntena* atual = (VAntena*)malloc(sizeof(VAntena));
    if (!atual) return NULL;
    atual->frequencia = freq;
    atual->linha = linha;
    atual->coluna = coluna;
    atual->listaAdj = NULL;
    atual->proximo = NULL;
    return atual;
}

/**
 * @brief Insere uma antena no grafo, se a posição estiver livre.
 * @param g Ponteiro para o grafo.
 * @param freq Frequência da antena.
 * @param linha Linha da antena.
 * @param coluna Coluna da antena.
 * @return true se inserido, false caso contrário.
 */

// Inserir antena na lista ligada
bool inserirAntena(Grafo* g, char freq, int linha, int coluna) {
    if (!g) return false;

    if (posicaoOcupada(g, linha, coluna)) {
        return false;
    }

    VAntena* novaAntena = criarAntena(freq, linha, coluna);
    if (!novaAntena) return false;

    novaAntena->proximo = g->listaAntenas;
    g->listaAntenas = novaAntena;
    g->numAntenas++;
    return true;
}

/**
 * @brief Remove uma antena da lista ligada do grafo (não remove adjacências).
 * @param g Ponteiro para o grafo.
 * @param freq Frequência da antena.
 * @param linha Linha da antena.
 * @param coluna Coluna da antena.
 * @return true se removido, false se não encontrado.
 */
// Remover antena da lista ligada
bool RemoverAntena(Grafo* g, char freq, int linha, int coluna) {
    VAntena* atual = g->listaAntenas;
    VAntena* Anterior = NULL;

    while (atual != NULL) {
        if (atual->frequencia == freq && atual->linha == linha && atual->coluna == coluna) {
            if (Anterior == NULL) {
                g->listaAntenas = atual->proximo;
            } else {
                Anterior->proximo = atual->proximo;
            }
            free(atual);
            g->numAntenas--;
            return true; // Removido com sucesso
        }
        Anterior = atual;
        atual = atual->proximo;
    }
    return false; // Não existe antena nessa posição
}

/**
 * @brief Verifica se já existe uma antena na posição dada.
 * @param g Ponteiro para o grafo.
 * @param linha Linha a verificar.
 * @param coluna Coluna a verificar.
 * @return true se a posição está ocupada, false caso contrário.
 */

// Verifica se já existe antena na mesma posição
bool posicaoOcupada(Grafo* g, int linha, int coluna) {
    if (!g || !g->listaAntenas) return false;

        VAntena* atual = g->listaAntenas;
    for (atual = g->listaAntenas; atual != NULL; atual = atual->proximo) {
        if (atual->linha == linha && atual->coluna == coluna) {
            return true;
        }
    }
    return false;
}

#pragma endregion
#endif