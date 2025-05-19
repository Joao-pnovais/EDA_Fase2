#ifndef GRAFO_H
#define GRAFO_H

#include "Dados.h"

/**
 * @file Grafo.h
 * @brief Funções para manipulação de grafos.
 * @author João Novais
 * @date 2025-05-18
 */

/**
 * @brief Cria um grafo vazio.
 * @return Ponteiro para o grafo criado.
 */
Grafo* criarGrafo();

/**
 * @brief Imprime o grafo.
 * @param g Ponteiro para o grafo.
 * @return true se impresso, false caso contrário.
 */
bool imprimirGrafo(Grafo* g);

/**
 * @brief Conecta automaticamente antenas do mesmo tipo.
 * @param g Ponteiro para o grafo.
 * @return true se conectou, false caso contrário.
 */
bool conectarAntenasMesmoTipo(Grafo* g);



/**
 * @brief Insere uma adjacência (ligação) entre duas antenas.
 * @param origem Ponteiro para a antena de origem.
 * @param destino Ponteiro para a antena de destino.
 * @return true se inserido, false caso contrário.
 */
bool inserirAdjacente(VAntena* origem, VAntena* destino);

/**
 * @brief Remove a ligação entre duas antenas.
 * @param origem Ponteiro para a antena de origem.
 * @param destino Ponteiro para a antena de destino.
 * @return true se removido, false caso contrário.
 */
bool removerAdjacente(VAntena* origem, VAntena* destino);


/**
 * @brief Cria uma nova antena.
 * @param freq Frequência da antena.
 * @param linha Linha da antena.
 * @param coluna Coluna da antena.
 * @return Ponteiro para a nova antena.
 */
VAntena* inserirVertice(Grafo* g, char freq, int linha, int coluna);

/**
 * @brief Remove uma antena do grafo.
 * @param g Ponteiro para o grafo.
 * @param freq Frequência.
 * @param linha Linha.
 * @param coluna Coluna.
 * @return true se removido, false caso contrário.
 */
bool removerVertice(Grafo* g, char freq, int linha, int coluna);

/**
 * @brief Limpa o campo 'visitado' de todas as antenas.
 * @param g Ponteiro para o grafo.
 * @return true após limpar.
 */
bool limparVisitados(Grafo* g);

/**
 * @brief Executa DFS a partir de uma antena.
 * @param ant Ponteiro para a antena inicial.
 * @return true se visitou, false caso contrário.
 */
bool DFS(VAntena* ant);

/**
 * @brief Imprime o resultado do DFS para todo o grafo.
 * @param g Ponteiro para o grafo.
 * @return true após imprimir.
 */
bool imprimirDFS(Grafo* g);

/**
 * @brief Verifica se dois segmentos de antenas cruzam.
 * @param x1, y1 Coordenadas do primeiro ponto do primeiro segmento.
 * @param x2, y2 Coordenadas do segundo ponto do primeiro segmento.
 * @param x3, y3 Coordenadas do primeiro ponto do segundo segmento.
 * @param x4, y4 Coordenadas do segundo ponto do segundo segmento.
 * @param ix Ponteiro para armazenar a coordenada x da interseção.
 * @param iy Ponteiro para armazenar a coordenada y da interseção.
 * @return true se cruzam, false caso contrário.
 */
bool segmentosCruzam(int x1, int y1, int x2, int y2,
    int x3, int y3, int x4, int y4, float* ix, float* iy);


/**
 * @brief Lê uma matriz de antenas de um ficheiro de texto e insere no grafo.
 * @param g Ponteiro para o grafo.
 * @param filename Nome do ficheiro de texto.
 * @param linhas Ponteiro para guardar o número de linhas.
 * @param colunas Ponteiro para guardar o número de colunas.
 * @return true se leu e inseriu com sucesso, false caso contrário.
 */
bool listarIntersecoesAntenasTipos(Grafo* g, char freq1, char freq2);

/**
 * @brief Executa uma busca em profundidade (DFS) a partir de uma antena.
 * @param atual Ponteiro para a antena inicial.
 * @param visitado Array de flags para marcar as antenas já visitadas (indexado por linha*100+coluna).
 * @return true se visitou pelo menos uma antena, false caso contrário.
 */
bool DFS_Antena(VAntena* atual, bool* visitado);

/**
 * @brief Executa DFS para todas as antenas do grafo, visitando todos os componentes.
 * @param g Ponteiro para o grafo.
 * @return true se pelo menos uma antena foi visitada, false caso contrário.
 */
bool DFSTraversal_Antena(Grafo* g);

/**
 * @brief Procura uma antena no grafo com frequência, linha e coluna especificadas.
 * @param g Ponteiro para o grafo.
 * @param freq Frequência da antena.
 * @param linha Linha da antena.
 * @param coluna Coluna da antena.
 * @return Ponteiro para a antena encontrada, ou NULL se não existir.
 */
VAntena* procurarAntena(Grafo* g, char freq, int linha, int coluna);

#endif