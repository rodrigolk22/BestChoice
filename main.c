#include "header.h"

/*
Ambiente GRID
Alunos:
Rodrigo Luiz Kovalski
William Villwock Fehrmann
*/


void main(){
    int M = 0;//Linhas
    int N = 0;//Colunas
    int i = 0;
    int j = 0;
    int total_parede = 0;
    int num_parede = 0;
    int ini_posX = -1;//Posicao inicial X
    int ini_posY = -1;
    int atual_X = -1;
    int atual_Y = -1;
    int fin_posX = -1;
    int fin_posY = -1;
    int direcao_destino = 0;
    int limite_grafo = 0;//Tamanho maximo de deslocamento do grafo
    printf("Bem vindo ao programa Abiente GRID\n");
    printf("\nUtilizando Grafo predefinido\n");
    M = 11;
    N = 11;
    // Alocando a matriz dinâmicamente
    int **vertice = malloc( M * sizeof (int *));
    for (i = 0; i < M; i++){
        vertice[i] = malloc( N * sizeof (int));
    }
    //Inicializa com 1 - chao
    for(i = 0;i < M;i++){
        for(j = 0;j < N;j++){
            vertice[i][j] = 1;
        }
    }
    limite_grafo = 12;//11 //limite de passos
    ini_posX = 0;//10
    ini_posY = 10;//5
    atual_X = ini_posX;
    atual_Y = ini_posY;
    fin_posX = 10;//0
    fin_posY = 5;//10
    num_parede = 15;//Mantenha este valor atualizado
    //parede 1
    vertice[3][4] = 0;
    vertice[3][5] = 0;
    vertice[3][6] = 0;
    //parede 2
    vertice[4][1] = 0;
    vertice[4][2] = 0;
    vertice[4][3] = 0;
    //parede 3
    vertice[4][7] = 0;
    vertice[4][8] = 0;
    vertice[4][9] = 0;
    //parede 4
    vertice[0][6] = 0;
    vertice[0][7] = 0;
    //parede 5
    vertice[1][5] = 0;
    vertice[1][7] = 0;
    //parede 6
    vertice[2][5] = 0;
    vertice[2][6] = 0;
    //vertice[2][7] = 0;

    printf("Etapa 3 - Construindo o GRID com os parametros fornecidos\n");
    int id = 1;
    for(i = 0;i < M;i++){
        printf("%d -", i);
        for(j = 0;j < N;j++){
            if(vertice[i][j] > 0){
                vertice[i][j] = id;
                if(vertice[i][j] <100){
                    printf(" ");
                }
                if(vertice[i][j] <10){
                    printf(" ");
                }
                if(i == M-ini_posX-1 && j == ini_posY){
                    printf(" M ");
                }
                else if(i == M-fin_posX-1 && j == fin_posY){
                    printf(" X ");
                }else{
                    printf(" %d ", vertice[i][j]);
                }
                id++;
            }
            else{
                printf(" ### ");
            }
        }
        printf("\n");
    }

    direcao_destino = retorna_direcao(ini_posX, ini_posY, fin_posX, fin_posY);
    printf("\nIniciando a busca inicio X %d Y %d final X %d Y %d\n", ini_posX, ini_posY, fin_posX, fin_posY);
    Graph *G = criar_grafo (M*N-num_parede, direcao_destino, limite_grafo, M, N);
    busca_best_choice(G, vertice, M-atual_X-1, atual_Y, M-fin_posX-1, fin_posY, 0, 0, 0);

    printf("\nImprimindo resultado final:\n");
    struct node *aux;
    for(i = 0;i < M;i++){
        printf("%d -", i);
        for(j = 0;j < N;j++){
            if(vertice[i][j] > 0){
                aux = G->listadj[i];
                if(vertice[i][j] <100){
                    printf(" ");
                }
                if(vertice[i][j] <10){
                    printf(" ");
                }
                if(i == M-ini_posX-1 && j == ini_posY){
                    printf(" M ");
                }
                else if(i == M-fin_posX-1 && j == fin_posY){
                    printf(" X ");
                }else{
                    printf(" %d ", vertice[i][j]);
                }
            }
            else{
                printf(" ### ");
            }
        }
        printf("\n");
    }

    free(G->listadj);
    for(i=0; i<M;i++){
        free(G->matrixadj[i]);
        free(vertice[i]);
    }
    free(G->matrixadj);
    free(G);
    free(vertice);

    exit(1);
}
