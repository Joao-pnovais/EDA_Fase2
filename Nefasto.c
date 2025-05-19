#ifndef NEFASTO_C
#define NEFASTO_C
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
 * @file Nefasto.c
 * @brief Implementação das funções para efeitos nefastos.
 * @author João Novais
 * @date 2025-05-18
 */

#pragma region Efeitos Nefastos

/**
 * @brief Cria um novo efeito nefasto.
 * @param linha Linha do efeito.
 * @param coluna Coluna do efeito.
 * @return Ponteiro para o efeito criado.
 */
EfeitoNefasto* CriarNafsto(int linha, int coluna) {
    EfeitoNefasto* novo = malloc(sizeof(EfeitoNefasto));
    novo->linha = linha;
    novo->coluna = coluna;
    novo->proximo = NULL;
    return novo;
}

/**
 * @brief Insere um efeito nefasto na lista.
 * @param lista Lista de efeitos nefastos.
 * @param linha Linha do novo efeito.
 * @param coluna Coluna do novo efeito.
 * @param freq Frequência associada ao efeito.
 * @return Ponteiro para o início da lista atualizada.
 */
EfeitoNefasto* inserirEfeito(EfeitoNefasto* lista, int linha, int coluna, char freq) {
    EfeitoNefasto* novo = malloc(sizeof(EfeitoNefasto));
    novo->linha = linha;
    novo->coluna = coluna;
    novo->frequencia = freq;
    novo->proximo = lista;
    return novo;
}

/**
 * @brief Verifica se já existe um efeito nefasto numa posição.
 * @param lista Lista de efeitos nefastos.
 * @param linha Linha a verificar.
 * @param coluna Coluna a verificar.
 * @return true se já existe, false caso contrário.
 */
bool existeEfeito(EfeitoNefasto* lista, int linha, int coluna) {
    for (EfeitoNefasto* novoefeito = lista; novoefeito != NULL; novoefeito = novoefeito->proximo) {
        if (novoefeito->linha == linha && novoefeito->coluna == coluna) {
            return true; // Efeito já existe
        }
    }
    return false;// Ainda não existe
}

/**
 * @brief Calcula todos os efeitos nefastos do grafo.
 * @param g Ponteiro para o grafo.
 * @param status Ponteiro para bool que indica se encontrou efeitos.
 * @return Lista ligada de efeitos nefastos encontrados, ou NULL se nenhum.
 */
EfeitoNefasto* calcularEfeitosNefastos(Grafo* g, bool* status) {
    if (!g || !g->listaAntenas) return NULL; // Grafo vazio

    EfeitoNefasto* listaEfeitos = NULL;
    VAntena* atual = g->listaAntenas;
    VAntena* atual2 = atual->proximo;

    // Se não há pelo menos duas antenas, não há efeitos nefastos
    if (!atual || !atual->proximo) return NULL;

    for (atual = g->listaAntenas; atual != NULL; atual = atual->proximo) {
        for (atual2 = atual->proximo; atual2 != NULL; atual2 = atual2->proximo) {
            if (atual->frequencia != atual2->frequencia) continue;

            int deltaLinha = atual2->linha - atual->linha;
            int deltaColuna = atual2->coluna - atual->coluna;

            int efeitoLinha1 = atual->linha - deltaLinha;
            int efeitoColuna1 = atual->coluna - deltaColuna;

            int efeitoLinha2 = atual2->linha + deltaLinha;
            int efeitoColuna2 = atual2->coluna + deltaColuna;

            if (efeitoLinha1 >= 0 && efeitoColuna1 >= 0 &&
                !existeEfeito(listaEfeitos, efeitoLinha1, efeitoColuna1))
                listaEfeitos = inserirEfeito(listaEfeitos, efeitoLinha1, efeitoColuna1, atual->frequencia);

            if (efeitoLinha2 >= 0 && efeitoColuna2 >= 0 &&
                !existeEfeito(listaEfeitos, efeitoLinha2, efeitoColuna2))
                listaEfeitos = inserirEfeito(listaEfeitos, efeitoLinha2, efeitoColuna2, atual->frequencia);
        }
    }
    if (status) *status = (listaEfeitos != NULL);
    return listaEfeitos;
}

/**
 * @brief Imprime a lista de efeitos nefastos.
 * @param lista Lista de efeitos nefastos.
 */
bool imprimirEfeitosNefastos(EfeitoNefasto* lista) {
    if (!lista) return false; // Nenhum efeito nefasto
    EfeitoNefasto* e = lista;

    printf("\nEfeitos nefastos:\nLinha\tColuna\tFreq\n");
    for (e = lista; e != NULL; e = e->proximo) {
        if (e->frequencia != '#') {
            printf(" %d\t  %d\t  %c\n", e->linha, e->coluna, e->frequencia);
        } else {
            // Se for efeito nefasto, imprime com '#'
            printf(" %d\t  %d\t  #\n", e->linha, e->coluna);
        }
    }
    return true;// Efeitos impressos com sucesso
}

/**
 * @brief Escreve o mapa atualizado no ficheiro, colocando '#' onde há efeito nefasto.
 * @param filename Nome do ficheiro a escrever.
 * @param g Ponteiro para o grafo.
 * @param efeitos Lista de efeitos nefastos.
 * @param linhas Número de linhas do mapa.
 * @param colunas Número de colunas do mapa.
 */
bool escreverMapaComEfeitos(const char* filename, Grafo* g, EfeitoNefasto* efeitos, int linhas, int colunas) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        return false;// Erro ao abrir o ficheiro
    }
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            // Verifica se há antena nesta posição
            VAntena* ant = g->listaAntenas;
            bool temAntena = false;
            char freq = '.';
            while (ant) {
                if (ant->linha == i && ant->coluna == j) {
                    temAntena = true;
                    freq = ant->frequencia;
                    break;
                }
                ant = ant->proximo;
            }
            // Verifica se há efeito nefasto nesta posição
            if (!temAntena && existeEfeito(efeitos, i, j)) {
                fputc('#', f);
            } else if (temAntena) {
                fputc(freq, f);
            } else {
                fputc('.', f);
            }
        }
        fputc('\n', f);
    }
    fclose(f);
    return true;// Mapa escrito com sucesso
}

#pragma endregion


#endif