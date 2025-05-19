#ifndef FICHEIROS_H
#define FICHEIROS_H

#include "Dados.h"
#include <stdbool.h>
/**
 * @file Ficheiros.h
 * @brief Funções para ler e escrever o grafo em ficheiros.
 * @author João Novais
 * @date 2025-05-18
 */



/**
 * @brief Lê uma matriz de antenas de um ficheiro de texto e insere no grafo.
 * @param g Ponteiro para o grafo.
 * @param filename Nome do ficheiro de texto.
 * @param linhas Ponteiro para guardar o número de linhas.
 * @param colunas Ponteiro para guardar o número de colunas.
 * @return true se leu e inseriu com sucesso, false caso contrário.
 */
bool lerMatrizAntenas(Grafo* g, const char* filename, int* linhas, int* colunas);

/**
 * @brief Guarda o grafo em ficheiro binário.
 * @param filename Nome do ficheiro binário.
 * @param g Ponteiro para o grafo.
 * @return true se guardou, false caso contrário.
 */
bool guardarBinario(const char* filename, Grafo* g);

/**
 * @brief Lê o grafo de um ficheiro binário.
 * @param filename Nome do ficheiro binário.
 * @param g Ponteiro para o grafo.
 * @return true se leu, false caso contrário.
 */
bool lerBinario(const char* filename, Grafo* g);


#endif