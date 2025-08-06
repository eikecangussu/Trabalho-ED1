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
    No *aux = p->topo;
    while (aux != NULL){
        aux = p->topo->ant;
        free(p->topo);
        p->topo = aux;
    }
    p->tamanho = 0;
    return p;
}

bool vazia(Pilha *p){
    if(p->topo == NULL) return true;
    else return false;
}

Pilha *empilha(Pilha *p, void *chave){
    No *novo = criaNo(chave);
    if (p->topo != NULL){
        p->topo->prox = novo;
        p->topo->prox->ant = p->topo;
        p->topo = p->topo->prox;
    }else{
        p->topo = novo;
    }
    p->tamanho++;
    return p;
}

void *desempilha(Pilha *p){
    void *removido = NULL;
    if(p->topo != NULL){
        No *aux = p->topo;
        p->topo = aux->ant;
        p->topo->prox = NULL;
        p->tamanho--;
        removido = aux->ch;
        free(aux);
    }
    return removido;
}

int tamanho(Pilha *p){
    return p->tamanho;
}
