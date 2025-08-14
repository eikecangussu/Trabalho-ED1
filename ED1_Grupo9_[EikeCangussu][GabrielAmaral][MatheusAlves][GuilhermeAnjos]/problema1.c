#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*

Função: validaExpTipoA

Descrição: Analisa a expressão numérica recebida e retorna se ela é valida para a estrutura do tipo A.

Entrada:
char *exp: string de caracteres com a expressão numérica.

Saída: 0 ou 1, sendo 0 se a expressão NÃO for válida para o tipo A e 1 se a expressão for válida.

*/

int validaExpTipoA(char *exp){
    Pilha *p = iniciaPilha();
    int valido = 1; // variavel flag de validação é iniciada como verdadeiro

    for(int i = 0; exp[i] != '\0'; i++){ // percorre cada caractere até chegar no fim '\0'
        char c = exp[i];
        if(c == '(' || c == '[' || c == '{'){  // verifica se o caratere é um delimitador de abertura
            char *elemento = (char*)malloc(sizeof(char)); 
            *elemento = c; // armazena o caractere
            empilha(p, elemento); // adiciona o caractere na pilha
        }

        else if( c == ')' || c == ']' || c == '}'){ // verifica se é um delimitador de fechamento
            if(vazia(p)){ // verifica se pilha está vazia ou seja se não existe abertura
                valido = 0; // se não existir abertura correspondente na pilha, marca a flag como invalida
                break;
            }

            char *topo = desempilha(p); // retira da pilha o ultimo delimitador e salva na variavel para fazer uma comparação
            if((c == ')' && *topo != '(') ||  // verifica se esse o delimitador de fechamento é diferente do de abertura
               (c == ']' && *topo != '[') ||
               (c == '}' && *topo != '{')) {
                valido = 0; // se for diferente, marca a flag como invalido
                free(topo); // libera memoria
                break;
            }

            free(topo); // libera memoria mesmo se não sastisfazer o condicional acima
        }
    }

    if(valido && !vazia(p)){ // verifica se após percorrer a expressão até o final ainda existe elementos na pilha
        valido = 0; // se ainda houver, significa que existem delimitadores em aberto na expressão marcando a flag como invalida
    }

    esvazia(p); //esvazia a pilha se ainda houverem elementos

    destroiPilha(p); // destroi a estrutura da pilha e limpa a memoria

    return valido; // retorno de validacao ou não da expressão, com 0 para invalido ou 1 para valido

}


/*

Função: validaExpTipoB

Descrição: Analisa a expressão numérica recebida e retorna se ela é valida para a estrutura do tipo B.

Entrada:
char *exp: string de caracteres com a expressão numérica.

Saída: 0 ou 1, sendo 0 se a expressão NÃO for válida para o tipo B e 1 se a expressão for válida.

*/

int validaExpTipoB(char * exp){
    Pilha *p = iniciaPilha();
    int valido = 1;  // variavel flag de validação é iniciada como verdadeiro

    for(int i = 0; exp[i] != '\0'; i++){ // percorre cada caractere até chegar no fim '\0'
        char c = exp[i];
        if(c == '(' || c == '[' || c == '{' ){ // verifica se o caratere é um delimitador de abertura
            if (!vazia(p)) { // verifica se a pilha nao esta vazia
                char* top_char = (char*)mostrarTopo(p); // vai obter o elemento do topo sem desempilhar
                
                if (c == '[') { // verifica se esta abrindo colchete e se o topo é parenteses
                    if (*top_char == '(') {
                        valido = 0; // marca flag como invalido
                        break;
                    }
                } else if (c == '{') { // verifica se esta abrindo chave e se o topo é colchete ou parenteses
                    if (*top_char == '(' || *top_char == '[') { // chave dentro de parenteses ou chave dentro de colchete
                        valido = 0; // marca flag como invalido
                        break;
                    }
                }
            }

            char *elemento = (char*)malloc(sizeof(char)); // se passou nas verificaões, o delimitador é alocado e empilhado
            *elemento = c;
            empilha(p, elemento);

        }

        else if(c == ')' || c == ']' || c == '}'){ // verifica se é um delimitador de fechamento
            if(vazia(p)){  // verifica se pilha está vazia ou seja se não existe abertura
                valido = 0;  // se não existir abertura correspondente na pilha, marca a flag como invalida
                break;
            }

            char *topo = desempilha(p);  // retira da pilha o ultimo delimitador e salva na variavel para fazer uma comparação
            if ((c == ')' && *topo != '(') ||  // verifica se esse o delimitador de fechamento é diferente do de abertura
                (c == ']' && *topo != '[') ||
                (c == '}' && *topo != '{')) {
                valido = 0;  // se for diferente, marca a flag como invalido
                free(topo);  // libera memoria
                break; 
            }

            free(topo);  // libera memoria mesmo se não sastisfazer o condicional acima
        }
 
    }
    
    if(valido && !vazia(p)){  // verifica se após percorrer a expressão até o final ainda existe elementos na pilha
        valido = 0;  // se ainda houver, significa que existem delimitadores em aberto na expressão marcando a flag como invalida
    }

    esvazia(p); //esvazia a pilha se ainda houverem elementos

    destroiPilha(p);  //destroi a estrutura da pilha e limpa a memoria

    return valido;  // retorno de validacao ou não da expressão, com 0 para invalido ou 1 para valido
}

int main(){
    
    char expressao[1000];
    fgets(expressao, sizeof(expressao), stdin);
    expressao[strcspn(expressao, "\n")] = '\0';
    

    if(validaExpTipoA(expressao) && validaExpTipoB(expressao)){
        printf("A expressão %s é validada pelas opções (a) e (b).\n", expressao);
    }else if(validaExpTipoA(expressao) && !validaExpTipoB(expressao)){
        printf("A expressão %s é validade apenas pela opção (a).\n", expressao);
    }else if(!validaExpTipoA(expressao) && validaExpTipoB(expressao)){
        printf("A expressão %s é validade apenas pela opção (b).\n", expressao);
    }else{
        printf("A expressão %s não é validade em nenhuma das opções.\n", expressao);
    }

    return 0;
}


