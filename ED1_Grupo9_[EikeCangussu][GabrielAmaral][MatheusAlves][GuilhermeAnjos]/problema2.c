/*
Grupo 9: 
Eike Cangussu 
Matheus Alves
Guilherme Lima
Gabriel Amaral
*/
#include "Pilha.h"
#include <string.h>

bool expressaoValida(char *infixa) {
    /*
        Verifica se a expressão infixa é válida
        Retorna true se for válida, false caso contrário
    */
    int parenCount = 0;
    for (int i = 0; infixa[i] != '\0'; i++) {
        if (infixa[i] == '(') {
            parenCount++;
        } else if (infixa[i] == ')') {
            parenCount--;
            if (parenCount < 0) return false; // Parênteses fechados sem correspondência
        }
    }

    return parenCount == 0; // Todos os parênteses devem estar balanceados
}

bool entradavalida( char exp){
    /*
        Verifica se o caracter é valido
        Caracteres validos são variáveis literais de A a J,
        operadores (+ (adição), - (subtração), / (divisão),* (multiplicação),^ (potenciação))
        e os delimitadores de escopo tipo parênteses ( “(”, “)”)
    */
    bool valida=false;
    if ((exp >= 'A' && exp <= 'J') || exp == '+' || exp == '-' || exp == '/' || exp == '*' || exp == '^' || exp == '(' || exp == ')')
    {
        valida=true;
        return valida;
    }
    else
    {
        return valida;
    }
}

bool operador(char exp){
    /*
        Verifica se o caracter é um operador
    */
    if (exp == '+' || exp == '-' || exp == '/' || exp == '*' || exp == '^')
    {
        return true;
    }
    return false;
}

int precedencia(char operador) {
    /*
        Retorna a precedência do operador
        Maior valor significa maior precedência
    */
    switch (operador) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0; // Para operadores não reconhecidos
    }
}

void converteInfixa(char *infixa)
{
    /*
        Converte uma expressão infixa para posfixa
        A expressão infixa é passada como parâmetro
        A expressão posfixa é impressa na tela
    */

    Pilha *pilha = iniciaPilha();
    int j = 0; // Índice para a string posfixa
    char posfixa[100]; // String para armazenar a expressão posfixa
    for (int i = 0; infixa[i] != '\0'; i++) {
        char c = infixa[i];

        if (entradavalida(c)) {
            
            if (c >= 'A' && c <= 'J') { // Se for uma variável literal
                posfixa[j++] = c;
            }
            else if (c == '(') { // Se for um parêntese de abertura
                char *elemento = (char*)malloc(sizeof(char));
                *elemento = c;
                empilha(pilha, elemento);
            }
            if (operador(c)) {
                if (vazia(pilha)) { // Pilha vazia
                    char *elemento = (char*)malloc(sizeof(char));
                    *elemento = c;
                    empilha(pilha, elemento);
                } else {
                    char *top = pilha->topo->ch;
                    if (c == '^') { // Tratamento especial para associatividade à direita
                        while (!vazia(pilha) && *top == '^') {
                            break; // Empilha o novo operador ^ junto ao topo
                        }
                    } else if (precedencia(*top) >= precedencia(c)) { // Menor ou igual precedência
                        while (!vazia(pilha) && precedencia(*top) >= precedencia(c)) {
                            char *topoElem = desempilha(pilha);
                            posfixa[j++] = *topoElem;
                            free(topoElem);
                            if (!vazia(pilha)) {
                                top = pilha->topo->ch;
                            }
                        }
                    }
                    char *elemento = (char*)malloc(sizeof(char));
                    *elemento = c;
                    empilha(pilha, elemento);
                }
            }
            else if (c == ')') { // Se for um parêntese de fechamento
                while (!vazia(pilha) && (*(char *)(pilha->topo->ch)) != '(') {
                    char *topoElem = desempilha(pilha);
                    posfixa[j++] = *topoElem;
                    free(topoElem);
                }
                if (!vazia(pilha)) {
                    desempilha(pilha); // Remove o '(' da pilha
                }
            }
        } else {
            printf("Entrada inválida: %c\n", c);
           return destroiPilha(pilha);
        }
        
    }
    
    // Desempilhar os operadores restantes na pilha
    while (!vazia(pilha)) {
        char *topoElem = desempilha(pilha);
        posfixa[j++] = *topoElem;
        free(topoElem);
    }
    
    //print posfixa
    printf("\nPosfixa: %.*s\n", j, posfixa);
    posfixa[j] = '\0'; // Finaliza a string posfixa
    destroiPilha(pilha);
}

int main() {
    /*
        Função principal que executa o programa
        Solicita ao usuário a expressão a ser convertida
        e chama a função de conversão
    */
    char infixa[100];
    int escolha = 0; // Inicializa a variável escolha
    
    // MENU DE OPÇÕES
    
    while (escolha != 3) {
        printf("Escolha o formato da expressao a ser inserida:\n");
        printf("1. Forma Posfixa\n");
        printf("2. Forma Infixa\n");
        printf("3. Sair\n");
        printf("Digite sua escolha: ");
        scanf("%d", &escolha);
        
        if (escolha == 1) {
            printf("Digite a expressao em forma Posfixa (use A-J como variaveis): ");
            getchar(); // Limpa o buffer do teclado
            fgets(infixa, sizeof(infixa), stdin);
            infixa[strcspn(infixa, "\n")] = 0; // Remove o newline
            printf("\nPosfixa:%s\n", infixa);
        } 
        else if (escolha == 2) {
            printf("Digite a expressao em forma Infixa (use A-J como variaveis): ");
            getchar(); // Limpa o buffer do teclado
            fgets(infixa, sizeof(infixa), stdin);
            infixa[strcspn(infixa, "\n")] = 0; // Remove o newline
            if(!expressaoValida(infixa)) {// Verifica se a expressão é válida
                printf("Erro: Parenteses nao balanceados na expressao.\n");
                continue; // Volta ao menu sem chamar converteInfixa
            }
            converteInfixa(infixa);
            
        } else if (escolha == 3) {
            printf("Saindo\n");
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }
    }

    return 0;
}