#ifndef __PILHA_H__
#define __PILHA_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Definição de estruturas */

typedef struct no{
    void* ch;
    struct no *prox;
}No;

typedef struct pilha{
    int tamanho;
    No *topo;
}Pilha;

/* Cabeçalho das funções com suas respectivas descrições*/

/*
Função: criaNo

Descrição: Aloca dinamicamente uma estrutura No e ...

Entrada:
void *chave: ponteiro para a chave de informação de tipo genérico guardada no nó.

Saída: Ponteiro para estrutura No alocada dinamicamente.

*/
No *criaNo(void *chave);

/*
Função: esvazia

Descrição: Esvazia a pilha removendo todos os seus elementos e ajustando o tamanho.

Entrada:
Pilha *p: Pilha a ser esvaziada.

Saída: Ponteiro para estrutura Pilha esvaziada.

*/
Pilha *esvazia(Pilha *p);

/*
Função: vazia

Descrição: Verifica se a Pilha está vazia e retorna o resultado

Entrada:
Pilha *p: Ponteiro para pilha a ser verificada.

Saída: Valor booleano para identificar se a estrutura está vazia ou não.

*/
bool vazia(Pilha *p);

/*
Função: empilha

Descrição: Adiciona um novo elemento no topo da pilha e atualiza o novo topo.

Entrada:
Pilha *p: Ponteiro para a pilha que receberá um novo elemento no seu topo.
void *novo: Ponteiro para dado de tipo genérico a ser inserido na pilha.

Saída: void.

*/
void empilha(Pilha *p, void *chave);

/*
Função: desempilha

Descrição: Exclui o elemento que está no topo da pilha, decrementa em um o tamanho, atualiza o novo topo e retorna o elemento removido.

Entrada:
Pilha *p: Ponteiro para a pilha a que terá um elemento excluído do seu topo.

Saída: void * Elemento removido da pilha ou NULL se a pilha já estiver vazia.

*/
void *desempilha(Pilha *p);

/*
Função: tamanho

Descrição: Identifica e retorna o número de elementos em uma pilha.

Entrada:
Pilha *p: Ponteiro para a pilha a ter seu tamanho checado.

Saída: Inteiro com o número de elementos da pilha.

*/
int tamanho(Pilha *p);

/*
Função: iniciaPilha

Descrição: Inicia uma pilha vazia.

Entrada: 
void

Saída: Ponteiro para pilha inicializada com tamanho = 0, topo = NULL

*/
Pilha *iniciaPilha();

/*
Função: destroiPilha(Pilha *P)

Descrição: Destroi completamente uma pilha vazia.

Entrada: 
Ponteiro para a pilha a ser destruida

Saida: void

*/
void destroiPilha(Pilha *p);

/*
Função: mostrarTopo(Pilha *P)

Descrição: Retorna o topo de uma pilha sem que ela seja desempilhada, ou NULL caso a pilha esteja vazia

Entrada: 
Ponteiro para a pilha que tera o topo exibido

Saida: void * Chave do elemento no topo da pilha ou NULL caso estiver vazia.

*/
void *mostrarTopo(Pilha *p);


#endif