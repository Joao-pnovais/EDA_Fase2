#ifndef ANTENA_H
#define ANTENA_H

#include "Dados.h"
#include <stdbool.h>

/**
 * @file Antena.h
 * @brief Funções relacionadas às antenas.
 * @author João Novais
 * @date 2025-05-18
 */
 

/**
 * @brief Cria uma nova antena.
 * @param freq Frequência da antena.
 * @param linha Linha da antena.
 * @param coluna Coluna da antena.
 * @return Ponteiro para a antena criada.
 */
VAntena* criarAntena(char freq, int linha, int coluna);

/**
 * @brief Insere uma antena no grafo.
 * @param g Ponteiro para o grafo.
 * @param freq Frequência.
 * @param linha Linha.
 * @param coluna Coluna.
 * @return true se inserida, false caso contrário.
 */
bool inserirAntena(Grafo* g, char freq, int linha, int coluna);

/**
 * @brief Remove uma antena da lista ligada do grafo.
 * @param g Ponteiro para o grafo.
 * @param freq Frequência.
 * @param linha Linha.
 * @param coluna Coluna.
 * @return true se removida, false caso contrário.
 */
bool RemoverAntena(Grafo* g, char freq, int linha, int coluna);

/**
 * @brief Verifica se uma posição está ocupada por uma antena.
 * @param g Ponteiro para o grafo.
 * @param linha Linha.
 * @param coluna Coluna.
 * @return true se ocupada, false caso contrário.
 */
bool posicaoOcupada(Grafo* g, int linha, int coluna);

#endif