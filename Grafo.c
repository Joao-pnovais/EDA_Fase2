#ifndef Grafo_c
#define Grafo_c
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
 * @file Grafo.c
 * @brief Implementação das funções do grafo.
 * @author João Novais
 * @date 2025-05-18
 */


#pragma region Grafo

/**
 * @brief Cria um grafo vazio.
 * @return Ponteiro para o grafo criado, ou NULL em caso de erro.
 */
// Criar grafo
Grafo* criarGrafo() {
    Grafo* g = (Grafo*)malloc(sizeof(Grafo));
    if (!g) return NULL;
    g->listaAntenas = NULL;
    g->numAntenas = 0;
    return g;
}

/**
 * @brief Imprime todas as antenas e as suas ligações do grafo.
 * @param g Ponteiro para o grafo.
 * @return true se o grafo foi a mostrado , false se o grafo está vazio ou é inválido.
 */
bool imprimirGrafo(Grafo* g) {
    if (!g || !g->listaAntenas) {
        return false;
    }
    int id = 0;
    for (VAntena* atual = g->listaAntenas; atual != NULL; atual = atual->proximo, id++) {
        if (atual->frequencia == '#') continue; // Ignora efeitos nefastos
        printf("Antena %c (%d,%d) -> ", atual->frequencia, atual->linha, atual->coluna);
        for (Adjacente* adj = atual->listaAdj; adj != NULL; adj = adj->proximo) {
            printf("(%c, %d,%d) ", adj->destino->frequencia, adj->destino->linha, adj->destino->coluna);
        }
        printf("\n");
    }
    return true;
}

/**
 * @brief Conecta automaticamente antenas do mesmo tipo.
 * @param g Ponteiro para o grafo.
 * @return true se conectou, false se o grafo está vazio.
 */
bool conectarAntenasMesmoTipo(Grafo* g) {
    if (!g || !g->listaAntenas) return false;

    for (VAntena* atual = g->listaAntenas; atual != NULL; atual = atual->proximo) {
        for (VAntena* outro = g->listaAntenas; outro != NULL; outro = outro->proximo) {
            if (atual != outro && atual->frequencia == outro->frequencia) {
                inserirAdjacente(atual, outro);
            }
        }
    }
    return true;
}

/**
 * @brief Insere uma adjacência (ligação) entre duas antenas.
 * @param origem Ponteiro para a antena de origem.
 * @param destino Ponteiro para a antena de destino.
 * @return true se inserido, false se já existia.
 */
bool inserirAdjacente(VAntena* origem, VAntena* destino) {
    if (!origem || !destino) return false;
    if (origem == destino) return false; // Impede auto-adjacências
    // Verifica se já existe ligação
    for (Adjacente* adj = origem->listaAdj; adj != NULL; adj = adj->proximo) {
        if (adj->destino == destino) return false;
    }
    Adjacente* novo = (Adjacente*)malloc(sizeof(Adjacente));
    if (!novo) return false;
    novo->destino = destino;
    novo->proximo = origem->listaAdj;
    origem->listaAdj = novo;
    return true;
}

/**
 * @brief Remove a ligação de origem para destino.
 * @param origem Ponteiro para a antena de origem.
 * @param destino Ponteiro para a antena de destino.
 * @return true se a ligação foi removida, false se não existia.
 */
// Remove atual ligação de origem para destino
bool removerAdjacente(VAntena* origem, VAntena* destino) {

    if (!origem || !origem->listaAdj) return false;

    Adjacente* atual = origem->listaAdj;
    Adjacente* anterior = NULL;

    while (atual) {
        if (atual->destino == destino) {
            if (anterior == NULL)
                origem->listaAdj = atual->proximo;
            else
                anterior->proximo = atual->proximo;
            free(atual);
            return true;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    return false; // Não encontrou atual adjacência
}


/**
 * @brief Cria uma nova antena.
 * @param freq Frequência da antena.
 * @param linha Linha da antena.
 * @param coluna Coluna da antena.
 * @return Ponteiro para a nova antena.
 */
VAntena* inserirVertice(Grafo* g, char freq, int linha, int coluna) {
    if (!g) return NULL;
    // Verifica se já existe antena nesta posição
    for (VAntena* a = g->listaAntenas; a != NULL; a = a->proximo) {
        if (a->linha == linha && a->coluna == coluna) return NULL;
    }
    VAntena* nova = (VAntena*)malloc(sizeof(VAntena));
    if (!nova) return NULL;
    nova->frequencia = freq;
    nova->linha = linha;
    nova->coluna = coluna;
    nova->visitado = 0;
    nova->listaAdj = NULL;
    nova->proximo = g->listaAntenas;
    g->listaAntenas = nova;
    g->numAntenas++;
    return nova;
}

/**
 * @brief Remove um vértice (antena) do grafo, removendo também todas as adjacências para ele.
 * @param g Ponteiro para o grafo.
 * @param freq Frequência da antena a remover.
 * @param linha Linha da antena a remover.
 * @param coluna Coluna da antena a remover.
 * @return true se removido, false se não encontrado.
 */
bool removerVertice(Grafo* g, char freq, int linha, int coluna) {
    if (!g || !g->listaAntenas) return false;// Grafo vazio

    VAntena* atual = g->listaAntenas;
    VAntena* percorrer = g->listaAntenas;
    VAntena* anterior = NULL;

    
    while (atual) {
        if (atual->frequencia == freq && atual->linha == linha && atual->coluna == coluna) {
            // Remove todas as adjacências de outros vértices para este
            for (percorrer = g->listaAntenas; percorrer != NULL; percorrer = percorrer->proximo) {
                if (percorrer != atual) removerAdjacente(percorrer, atual);
            }
            // Remove adjacências deste vértice
            Adjacente* adj = atual->listaAdj;
            while (adj) {
                Adjacente* temp = adj;
                adj = adj->proximo;
                free(temp);
            }
            // Remove da lista ligada
            if (anterior == NULL)
                g->listaAntenas = atual->proximo;
            else
                anterior->proximo = atual->proximo;
            free(atual);
            g->numAntenas--;
            return true;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    return false;
}

/**
 * @brief Limpa o campo 'visitado' de todas as antenas do grafo.
 * @param g Ponteiro para o grafo.
 * @return true após limpar.
 */
bool limparVisitados(Grafo* g) {
    for (VAntena* atual = g->listaAntenas; atual != NULL; atual = atual->proximo) {
        atual->visitado = false;
    }
    return true;
}

/**
 * @brief Executa uma busca em profundidade (DFS) a partir de uma antena.
 * @param atual Ponteiro para a antena inicial.
 * @return true se visitou, false caso contrário.
 */

 bool DFS(VAntena* atual) {
    if (!atual || atual->visitado) return false;

    if (atual->frequencia != '#') {
        atual->visitado = true;
        printf("Antena %c (%d,%d) visitada \n", atual->frequencia, atual->linha, atual->coluna);
    }

    for (Adjacente* adj = atual->listaAdj; adj != NULL; adj = adj->proximo) {
        DFS(adj->destino);
    }
    return true;
}



/**
 * @brief Imprime o resultado do DFS para todo o grafo.
 * @param g Ponteiro para o grafo.
 * @return true após imprimir.
 */
bool imprimirDFS(Grafo* g) {
   
    VAntena* atual = g->listaAntenas;
    if (!g || !g->listaAntenas) return false; // Grafo vazio

    for (atual = g->listaAntenas; atual != NULL; atual = atual->proximo) {
        if (!atual->visitado) {
            DFS(atual);
        }
    }
    return true;// Se todos visitados, retorna verdadeiro
}



/**
 * @brief Verifica se dois segmentos se cruzam e calcula o ponto de interseção.
 * @param x1,y1,x2,y2 Coordenadas do primeiro segmento.
 * @param x3,y3,x4,y4 Coordenadas do segundo segmento.
 * @param ix Ponteiro para guardar a coordenada x da interseção.
 * @param iy Ponteiro para guardar a coordenada y da interseção.
 * @return true se cruzam, false caso contrário.
 */

// Função auxiliar para verificar se dois segmentos se cruzam e calcular o ponto de interseção
bool segmentosCruzam(int x1, int y1, int x2, int y2,
                     int x3, int y3, int x4, int y4, float* ix, float* iy) {
    float denom = (float)((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4));
    if (denom == 0) return false; // Paralelos

    float intersecaoX = ((x1*y2 - y1*x2)*(x3 - x4) - (x1 - x2)*(x3*y4 - y3*x4)) / denom;
    float intersecaoY = ((x1*y2 - y1*x2)*(y3 - y4) - (y1 - y2)*(x3*y4 - y3*x4)) / denom;

    // Verifica se o ponto está dentro dos dois segmentos
    if (intersecaoX < fmin(x1, x2) || intersecaoX > fmax(x1, x2) ||
        intersecaoX < fmin(x3, x4) || intersecaoX > fmax(x3, x4) ||
        intersecaoY < fmin(y1, y2) || intersecaoY > fmax(y1, y2) ||
        intersecaoY < fmin(y3, y4) || intersecaoY > fmax(y3, y4))
        return false;

    *ix = intersecaoX;
    *iy = intersecaoY;
    return true;
}

/**
 * @brief Lista as interseções entre segmentos de dois tipos de antenas.
 * @param g Ponteiro para o grafo.
 * @param freq1 Frequência do primeiro tipo de antena.
 * @param freq2 Frequência do segundo tipo de antena.
 * @return true se encontrou interseções, false caso contrário.
 */

bool listarIntersecoesAntenasTipos(Grafo* g, char freq1, char freq2) {
    if (!g || !g->listaAntenas) return false; // Grafo vazio
    printf("Interseções reais entre segmentos %c-%c e %c-%c:\n", freq1, freq1, freq2, freq2);
    bool encontrou = false;
    VAntena* a1 = g->listaAntenas;
    VAntena* a2 = a1->proximo;
    VAntena* b1 = g->listaAntenas;
    VAntena* b2 = b1->proximo;


    // Para cada par de antenas freq1 (ex: A-A)
    for (a1 = g->listaAntenas; a1 != NULL; a1 = a1->proximo) {
        if (a1->frequencia != freq1) continue;
        for (a2 = a1->proximo; a2 != NULL; a2 = a2->proximo) {
            if (a2->frequencia != freq1) continue;
            // Para cada par de antenas freq2 (ex: B-B)
            for (b1 = g->listaAntenas; b1 != NULL; b1 = b1->proximo) {
                if (b1->frequencia != freq2) continue;
                for (b2 = b1->proximo; b2 != NULL; b2 = b2->proximo) {
                    if (b2->frequencia != freq2) continue;
                    float ix, iy;
                    if (segmentosCruzam(a1->linha, a1->coluna, a2->linha, a2->coluna,
                                        b1->linha, b1->coluna, b2->linha, b2->coluna,
                                        &ix, &iy)) {
                        printf("Segmento %c(%d,%d)-%c(%d,%d) x %c(%d,%d)-%c(%d,%d) -> Interseção em (%.2f,%.2f)\n",
                            a1->frequencia, a1->linha, a1->coluna, a2->frequencia, a2->linha, a2->coluna,
                            b1->frequencia, b1->linha, b1->coluna, b2->frequencia, b2->linha, b2->coluna,
                            ix, iy);
                        encontrou = true;
                    }
                }
            }
        }
    }
    if (!encontrou) return false; // Nenhuma interseção encontrada
    return encontrou;// Interseções encontradas
}

/**
 * @brief Executa uma busca em profundidade (DFS) a partir de uma antena.
 * @param atual Ponteiro para a antena inicial.
 * @param visitado Array de flags para marcar as antenas já visitadas (indexado por linha*100+coluna).
 * @return true se visitou pelo menos uma antena, false caso contrário.
 */
bool DFS_Antena(VAntena* atual, bool* visitado) {
    if (!atual) return false;
    int idx = atual->linha * 100 + atual->coluna; // Supondo linhas/colunas < 100
    if (visitado[idx]) return false; // Já visitado

    visitado[idx] = true;
    printf("Antena %c (%d,%d)\n", atual->frequencia, atual->linha, atual->coluna);

    for (Adjacente* adj = atual->listaAdj; adj != NULL; adj = adj->proximo) {
        int proxIdx = adj->destino->linha * 100 + adj->destino->coluna;
        if (!visitado[proxIdx]) {
            DFS_Antena(adj->destino, visitado);
        }
    }
    return true;
}

/**
 * @brief Executa DFS para todas as antenas do grafo, visitando todos os componentes.
 * @param g Ponteiro para o grafo.
 * @return true se pelo menos uma antena foi visitada, false caso contrário.
 */
bool DFSTraversal_Antena(Grafo* g) {
    if (!g || !g->listaAntenas) return false;
    bool visitado[10000] = {0}; // Ajusta o tamanho conforme necessário
    bool algumVisitado = false;
    for (VAntena* a = g->listaAntenas; a != NULL; a = a->proximo) {
        int idx = a->linha * 100 + a->coluna;
        if (!visitado[idx]) {
            if (DFS_Antena(a, visitado))
                algumVisitado = true;
        }
    }
    return algumVisitado;
}

/**
 * @brief Procura uma antena no grafo com frequência, linha e coluna especificadas.
 * @param g Ponteiro para o grafo.
 * @param freq Frequência da antena.
 * @param linha Linha da antena.
 * @param coluna Coluna da antena.
 * @return Ponteiro para a antena encontrada, ou NULL se não existir.
 */
VAntena* procurarAntena(Grafo* g, char freq, int linha, int coluna) {
    for (VAntena* a = g->listaAntenas; a != NULL; a = a->proximo) {
        if (a->frequencia == freq && a->linha == linha && a->coluna == coluna)
            return a;
    }
    return NULL;
}


#pragma endregion
#endif