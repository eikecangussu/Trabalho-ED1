/*
Grupo 9:
Eike Cangussu
Matheus Alves
Guilherme Lima
Gabriel Amaral
*/

#include "pilha.h"
#include <string.h>
#define MAX 1000       /* Define o tamanho maximo da matriz*/
char mapa[MAX][MAX];   /* Variavel para o mapa */
int visitou[MAX][MAX]; /* Variavel para saber qual parte do mapa visitou (se sim = 1, se nao = 0) */

typedef struct posicao /* Estrutura para guardar uma posicao no mapa ( sendo x = linhas e y = colunas)*/
{
    int x, y;
} Posicao;

int dy[4] = {-1, 1, 0, 0}; /* Direcao para cima e para baixo */
int dx[4] = {0, 0, -1, 1}; /* Direcao para esquerda e para direita */

void buscaComodo(int n, int m, int i, int j) /* Funçao para buscar comodos */
{
    Pilha *p = iniciaPilha(); /* cria uma pilha vazia */

    Posicao *inicio = (Posicao *)malloc(sizeof(Posicao)); /* aloca memoria para a posicao inicial */
    if (inicio == NULL)                                   /*verifica se conseguiu alocar a memoria*/
    {
        printf("ERRO de Alocação!");
        exit(1);
    }
    /*define as posicoes inicais*/
    inicio->x = i;
    inicio->y = j;
    empilha(p, inicio); /*coloca a posical inicial na pilha*/
    visitou[i][j] = 1;  /*marca a posicao inicial como visitada*/
    while (!vazia(p))   /*enquanto a pilha nao estiver vazia fica rodando*/
    {
        Posicao *atual = desempilha(p); /*retira o elemento do topo da pilha*/
        for (int d = 0; d < 4; d++)     /*percorrer as 4 direcoes*/
        {
            int ni = atual->x + dy[d];                  /*pula para a proxima linha*/
            int mj = atual->y + dx[d];                  /*pula para a proxima coluna*/
            if (ni >= 0 && ni < n && mj >= 0 && mj < m) /*verifica se está dentro do limite do mapa*/
            {
                if (!visitou[ni][mj] && mapa[ni][mj] == '.') /*verifica se ainda nao visitou e é um piso*/
                {
                    visitou[ni][mj] = 1;                     /*marca como visitado*/
                    Posicao *nova = malloc(sizeof(Posicao)); /*cria uma nova posicao para empilhar*/
                    if (nova == NULL)                        /*verifica a alocacao de memoria */
                    {
                        printf("ERRO de Alocação!");
                        exit(1);
                    }
                    nova->x = ni;
                    nova->y = mj;
                    empilha(p, nova); /*empilha a nova posicao*/
                }
            }
        }
        free(atual); /*libera a memoria da posicao atual*/
    }
    destroiPilha(p); /*libera toda a memoria usada pela pilha*/
}

int main()
{
    int comodos = 0; /*contador de comodos*/
    char linha[MAX]; /*buffer para ler as linhas do terminal*/
    /*Lê as dimensoes do mapa */
    int n, m; /*variaveis*/
    if (scanf("%d %d", &n, &m) != 2)
    {
        printf("Erro na leitura de n e m.\n");
        return 1;
    }

    while (getchar() != '\n')
        ;                                       /* limpa o buffer do teclado*/
    if (n <= 0 || m <= 0 || n > MAX || m > MAX) /*verifica os valores de n , m*/
    {
        printf("Dimensoes invalidas! Informe valores entre 1 e %d.\n", MAX);
        return 1;
    }
    /* Leitura do mapa */
    for (int i = 0; i < n; i++)
    {
        if (fgets(linha, sizeof(linha), stdin) == NULL) /*verifica a leitura da linha*/
        {
            printf("Erro na leitura do mapa.\n");
            return 1;
        }
        linha[strcspn(linha, "\n")] = '\0'; /* remove o \n se houver */
        for (int j = 0; j < m; j++)
        {
            mapa[i][j] = linha[j];
            visitou[i][j] = 0; /* marca como não visitada */
        }
    }

    /*Busca por comodos*/
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mapa[i][j] == '.' && !visitou[i][j]) /* verifica se encontrou um piso nao visitado*/
            {
                buscaComodo(n, m, i, j); /*marca todo o comodo*/
                comodos++;               /*incrementa a contagem de comodos*/
            }
        }
    }

    printf("%d\n", comodos); /* escreve no terminal a quantidade de cômodos*/

    return 0; /*encerra o programa*/

}
