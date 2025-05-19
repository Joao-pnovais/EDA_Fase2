#ifndef DADOS_H
#define DADOS_H
/**
 * @file Dados.h
 * @brief Estruturas de dados para o grafo de antenas e efeitos nefastos.
 * @author João Novais
 * @date 2025-05-18
 * 
 */


 /**
  * @brief Estrutura para representar um grafo de antenas.
  * @details Cada antena é representada por um nó na lista ligada, e cada nó contém uma lista de adjacências.
  * 
  */
typedef struct Adjacente {
    struct VAntena* destino;
    struct Adjacente* proximo;
} Adjacente;

/**
 * @brief Estrutura para representar uma antena.
 * @details Cada antena tem uma frequência, coordenadas (linha e coluna), um indicador de visitado e uma lista de adjacências.
 * 
 */

typedef struct VAntena {
    char frequencia;
    int linha, coluna;
    bool visitado;
    struct Adjacente* listaAdj;
    struct VAntena* proximo;
} VAntena;

/**
 * @brief Estrutura para representar o grafo de antenas.
 * @details Contém um ponteiro para a lista de antenas e o número total de antenas.
 * 
 */
typedef struct Grafo {
    VAntena* listaAntenas;
    int numAntenas;
} Grafo;


/**
 * @brief Estrutura para representar um efeito nefasto.
 * @details Cada efeito nefasto tem coordenadas (linha e coluna), uma frequência e um ponteiro para o próximo efeito nefasto.
 * 
 */
typedef struct EfeitoNefasto {
    int linha, coluna;
    char frequencia;
    struct EfeitoNefasto* proximo;
} EfeitoNefasto;


#endif