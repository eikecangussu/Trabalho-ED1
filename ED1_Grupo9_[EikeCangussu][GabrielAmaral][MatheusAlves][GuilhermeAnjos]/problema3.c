/*
Grupo 9: 
Eike Cangussu 
Matheus Alves
Guilherme Lima
Gabriel Amaral
*/

#include "pilha.h"
#include <string.h>
#define MAX 1000 /*Defini o tamanho maximo da matriz*/

typedef struct posicao /* estrutura para guardar uma posicao no mapa ( sendo x = linhas e y = colunas)*/
{
    int x, y;
} Posicao;

char mapa[MAX][MAX];   /*variavel para o mapa*/
int visitou[MAX][MAX]; /*variavel para saber qual parte do mapa visitou (se sim = 1, se nao = 0)*/
int n, m;              /*variaveis globais para numero de linhas(n) e coplunas(m) do mapa*/

int dy[4] = {-1, 1, 0, 0}; /*direcao para cima e para baixo*/
int dx[4] = {0, 0, -1, 1}; /*direcao para esquerda e para direita*/

void buscaComodo(int i, int j) /*Funçao para buscar comodos*/
{
    Pilha *p = iniciaPilha(); /*cria uma pilha vazia*/

    Posicao *inicio = (Posicao *)malloc(sizeof(Posicao)); /*aloca memoria para a posicao inicial*/
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

int main(int argc, char *argv[])
{

    if (argc != 3) /* Verifica se passou os 2 parametros (entrada e saída)*/
    {
        printf("Uso: %s <arquivo_entrada> <arquivo_saida>\n", argv[0]);
        return 1;
    }

    int comodos = 0; /*contador de comodos*/
    char linha[100]; /*buffer para ler as linhas do arquivo*/

    FILE *arquivoEntrada = fopen(argv[1], "r"); /* Abre o arquivo de entrada para leitura*/
    if (arquivoEntrada == NULL)                 /*verifica se conseguiu abrir o arquivo*/
    {
        printf("Não foi possivel abrir o arquivo!\n");
        return 1;
    }

    /* vai ler o mapa do arquivo e o armazenar  em matriz*/
    n = 0;                                                      /*numero de linhas lidas*/
    while (fgets(linha, sizeof(linha), arquivoEntrada) != NULL) /*le uma linha do arquivo ate retornar NULL*/
    {
        linha[strcspn(linha, "\n")] = '\0'; /*remove o \n se houver*/
        m = strlen(linha);                  /*recebe a largura da linha*/
        for (int j = 0; j < m; j++)         /*copia cada caractere da linha para a matriz do mapa*/
        {
            mapa[n][j] = linha[j];
            visitou[n][j] = 0; /*marca como nao visitada*/
        }
        n++; /*avança para a proxima linha*/
    }
    fclose(arquivoEntrada); /*fecha o arquivo*/

    /*Busca por comodos*/
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mapa[i][j] == '.' && !visitou[i][j]) /*verifica se encontrou um piso nao visitado*/
            {
                buscaComodo(i, j); /*marca todo o comodo*/
                comodos++;         /*incrementa a contagem de comodos*/
            }
        }
    }

    FILE *arquivoSaida = fopen(argv[2], "w"); /* Abre o arquivo de saída para escrita*/
    if (arquivoSaida == NULL)                 /* Verifica se conseguiu abrir o arquivo de saida*/
    {
        printf("Não foi possível abrir o arquivo de saída!\n");
        return 1;
    }

    fprintf(arquivoSaida, "%d\n", comodos); /* Escreve no arquivo a quantidade de cômodos*/
    fclose(arquivoSaida);                   /* Fecha o arquivo de saída */

    return 0; /*encerra o programa*/
}