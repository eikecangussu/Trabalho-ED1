/*
Grupo 9: 
Eike Cangussu 
Matheus Alves
Guilherme Lima
Gabriel Amaral
*/

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
    if(p->topo == NULL) return true; //Verifica se a pilha é vazia
    else return false;
}

void empilha(Pilha *p, void *chave){
    No *novo = criaNo(chave); // Aloca o novo nó e atribui o valor a nova chave
    novo->prox = p->topo; // Aponta o novo nó para o topo atual
    p->topo = novo; // Torna o novo nó o topo
    p->tamanho++; // Aumenta o tamanho da pilha
}

void *desempilha(Pilha *p){
    void *removido = NULL; // Inicializa a variável removido, que guarda o nó que será removido da pilha
    if(p->topo != NULL){ // Verifica se a pilha está vazia
        removido = p->topo->ch; // Guarda a chave do topo atual que será removida
        No *aux = p->topo; // Guarda o nó do topo em uma variável auxiliar
        p->topo = p->topo->prox; // Atualiza o topo da lista para o nó abaixo dele
        free(aux); // Libera a memória do antigo topo
    }
    return removido;
}

int tamanho(Pilha *p){
    return p->tamanho; // Retorna o tamanho da pilha
}

void destroiPilha(Pilha *p){
    if (p != NULL){ // Verifica se a a estrutura pilha está vazia
        esvazia(p); // Esvazia a lista encadeada dentro da pilha liberando a memória
        free(p); // Libera a mémoria da estrutura pilha
    }
}

void *mostrarTopo(Pilha *p){
    if(vazia(p)){ // Verifica se o topo da pilha está vazio
        return NULL; // Retorna NULL caso o topo da pilha está vazio
    }
    return p->topo->ch; // Retorna a chave do topo caso o topo da pilha seja diferente de NULL

}
