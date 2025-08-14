#include "pilha.h"

No *criaNo(void *chave){
    No *novo = (No *) calloc(1,sizeof(No)); //Aloca o novo nó e preenche os campos com valores default
    if(novo == NULL){printf("Erro:\n"); exit(1);} //Printa erro em caso de erro na alocação
    novo->ch = chave;//Atribui a chave ao novo nó
    return novo;
}

Pilha *iniciaPilha(){
    Pilha *p = (Pilha *) calloc(1,sizeof(Pilha)); //Aloca a nova pilha e preenche os campos com valores default
    if (p == NULL) {printf("Erro de alocacao da pilha"); exit(1);}
    return p;
}

Pilha *esvazia(Pilha *p){
    No *aux; // Variável auxiliar que guardará o topo antes de atualiza-lo
    while (p->topo != NULL){ //Só para após a pilha estar vazia
        aux = p->topo; // Guarda o ponteiro para o topo atual, para que a referencia não seja perdida, e o nó possa ser liberado
        p->topo = p->topo->prox; // Atualiza o topo para o elemento abaixo
        free(aux); // Libera o nó que estava com o topo anterior
    }
    p->tamanho = 0; // Atualiza o tamanho
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

void destroiPilha(Pilha *p){
    if (p != NULL){
        esvazia(p);
        free(p);
    }
}

void *mostrarTopo(Pilha *p){
    if(vazia(p)){
        return NULL;
    }
    return p->topo->ch;
}