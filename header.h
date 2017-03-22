#include <stdio.h>
#include <stdlib.h>

//#define DEBUG//Imprime informações de debug
#define MAX 99

//Direcoes baseadas no numpad do teclado
#define NO 7 //Noroeste
#define NN 8 //Norte
#define NE 9 //Nordeste
#define OO 4 //Oeste
#define LL 6 //Leste
#define SO 1 //Sudoeste
#define SS 2 //Sul
#define SE 3 //Sudeste

//Lista encadeada para guardar os vizinhos de cada no
typedef struct node {
    int id;//Identificação do vértice
    int anterior;//Id do vértice pai
    struct node *proximo;
} Node;
//Grafo
typedef struct graph {
    int V;//Numero de vértices no Grafo
    int E;//Numero de arestas no Grafo
    int limite_grafo;//Limite de procurado grafo
    int M;//impedir leituras fora do limite
    int N;//impedir leituras fora do limite
    int direcao_destino;//direcao que aponta o no destino
    int prio[8];//Direcoes onde a busca deve seguir primeiro
    int *visitados;//Nos ja visitados
    Node **listadj;//Lista de adjacencias
    int **matrixadj;//Matriz de adjacencias
} Graph;


//Funcoes de grafos
Graph* criar_grafo (int V, int direcao_destino, int limite_grafo, int M, int N);
void adicionar_aresta (Graph *G, int u, int v, int anterior);
int **inicializa_matriz_de_adjacencias (int r, int c, int w);
Node* criar_vertice (int v, Node *lista, int anterior);
void remover_aresta (Graph *G, int u, int v);
void print_grafo(Graph *G);

//Funcoes do Grid
void ir(Graph *G, int direcao);
void lerPos();

//Retorna direcao ao ponto final
int retorna_direcao(int origemX, int origemY, int destinoX, int destinoY);
void construir_prio(int* prio, int direcao);
int direcao_oposta(int* prio, int direcao);

//Funcao de busca
void busca_best_choice(Graph *G, int** vertice, int atual_posX, int atual_posY, int fin_posX, int fin_posY, int passo, int anterior, int tentativa);
