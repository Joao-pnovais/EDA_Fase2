#ifndef DADOS_H
#define DADOS_H

typedef struct Adjacente {
    struct VAntena* destino;
    struct Adjacente* proximo;
} Adjacente;

typedef struct VAntena {
    char frequencia;
    int linha, coluna;
    bool visitado;
    struct Adjacente* listaAdj;
    struct VAntena* proximo;
} VAntena;

typedef struct Grafo {
    VAntena* listaAntenas;
    int numAntenas;
} Grafo;

typedef struct EfeitoNefasto {
    int linha, coluna;
    char frequencia;
    struct EfeitoNefasto* proximo;
} EfeitoNefasto;


#endif