#ifndef NEFASTO_H
#define NEFASTO_H

#include "Dados.h"
/**
 * @file Nefasto.h
 * @brief Funções para manipulação de efeitos nefastos.
 * @author João Novais
 * @date 2025-05-18
 */

/**
 * @brief Cria um novo efeito nefasto.
 * @param linha Linha do efeito.
 * @param coluna Coluna do efeito.
 * @return Ponteiro para o efeito criado.
 */
EfeitoNefasto* CriarNafsto(int linha, int coluna);

/**
 * @brief Insere um efeito nefasto na lista.
 * @param lista Lista de efeitos nefastos.
 * @param linha Linha.
 * @param coluna Coluna.
 * @param freq Frequência.
 * @return Ponteiro para o início da lista atualizada.
 */
EfeitoNefasto* inserirEfeito(EfeitoNefasto* lista, int linha, int coluna, char freq);

/**
 * @brief Calcula todos os efeitos nefastos do grafo.
 * @param g Ponteiro para o grafo.
 * @param status Ponteiro para bool que indica se encontrou efeitos.
 * @return Lista ligada de efeitos nefastos encontrados, ou NULL se nenhum.
 */
EfeitoNefasto* calcularEfeitosNefastos(Grafo* g, bool* status);

/**
 * @brief Verifica se já existe um efeito nefasto numa posição.
 * @param lista Lista de efeitos nefastos.
 * @param linha Linha.
 * @param coluna Coluna.
 * @return true se já existe, false caso contrário.
 */
bool existeEfeito(EfeitoNefasto* lista, int linha, int coluna);

/**
 * @brief Imprime a lista de efeitos nefastos.
 * @param lista Lista de efeitos nefastos.
 */
bool imprimirEfeitosNefastos(EfeitoNefasto* lista);

/**
 * @brief Escreve o mapa atualizado no ficheiro, colocando '#' onde há efeito nefasto.
 * @param filename Nome do ficheiro a escrever.
 * @param g Ponteiro para o grafo.
 * @param efeitos Lista de efeitos nefastos.
 * @param linhas Número de linhas do mapa.
 * @param colunas Número de colunas do mapa.
 */
bool escreverMapaComEfeitos(const char* filename, Grafo* g, EfeitoNefasto* efeitos, int linhas, int colunas);

#endif