#include "pilha.h"

No *criaNo(void *chave){
    No *novo = (No *) calloc(1,sizeof(No));
    if(novo == NULL){printf("Erro:\n"); exit(1);}
    novo->ch = chave;
    return novo;
}

Pilha *iniciaPilha(){
    Pilha *p = (Pilha *) calloc(1,sizeof(Pilha));
    if (p == NULL) {printf("Erro de alocacao da pilha"); exit(1);}
    return p;
}

Pilha *esvazia(Pilha *p){
    No *aux;
    while (p->topo != NULL){
        aux = p->topo;
        p->topo = p->topo->prox;
        free(aux);
    }
    p->tamanho = 0;
    return p;
}

bool vazia(Pilha *p){
    if(p->topo == NULL) return true;
    else return false;
}

void empilha(Pilha *p, void *chave){
    No *novo = criaNo(chave);
    novo->prox = p->topo;
    p->topo = novo;
    p->tamanho++;
}

void *desempilha(Pilha *p){
    void *removido = NULL;
    if(p->topo != NULL){
        removido = p->topo->ch;
        No *aux = p->topo;
        p->topo = p->topo->prox;
        free(aux);
    }
    return removido;
}

int tamanho(Pilha *p){
    return p->tamanho;
}
