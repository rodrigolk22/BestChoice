#include "header.h"


//Cria um grafo dado o numero de vertices
Graph* criar_grafo (int V, int direcao_destino,  int limite_grafo, int M, int N) {
    Graph *G = (Graph *)malloc(sizeof(Graph));//Espaco para o grafo
    G->V = V;//Vertices
    G->E = 0;//Inicia sem arestas
    G->M = M;
    G->N = N;
    G->direcao_destino = direcao_destino;
    G->limite_grafo = limite_grafo;
    construir_prio(G->prio, direcao_destino);
    G->visitados = (int *)malloc(M * N * sizeof (int));
    G->listadj = (Node **)malloc(V * sizeof (Node *));
    int v;
    for (v = 0; v < V; v++){
        G->listadj[v] = NULL;
        G->visitados[v] = 0;
    }
    //Inicializa a matrix de adjacencia
    G->matrixadj = inicializa_matriz_de_adjacencias (V, V, 0);
    #ifdef DEBUG2
    printf("\nCriar grafo:  Grafo criado com sucesso\n");
    #endif
    return G;
}
//inicializa a matriz de adjacencias
int **inicializa_matriz_de_adjacencias (int r, int c, int w) {
    int i, j;
    int **mat = malloc( r * sizeof (int *));
    for (i = 0; i < r; i++){
        mat[i] = malloc( c * sizeof (int));
    }
    for (i = 0; i < r; i++){
        for (j = 0; j < c; j++){
        mat[i][j] = w;
        }
    }
    #ifdef DEBUG2
    printf("\nInicializa_matriz_de_adjacencias: Matriz de adjacencia criada com sucesso\n");
    #endif
    return mat;
}
//Adiciona aresta
void adicionar_aresta (Graph *G, int u, int v, int anterior) {
    Node *aux;
    #ifdef DEBUG2
    printf("\nAdicionar aresta: Adicionando aresta %d -> %d", u, v);
    #endif
    for (aux = G->listadj[u-1]; aux != NULL; aux = aux->proximo){
        if (aux->id == v){
            #ifdef DEBUG2
            printf("\nAdicionar aresta:  Aresta ja existe na lista de adjacencia!");
            #endif
            return;
        }
    }

    //Cria o vertice
    G->listadj[u-1] = criar_vertice (v, G->listadj[u-1], u);
    //Adiciona o peso na matriz de adjacencias
    G->matrixadj[u-1][v] = 1;
    //Acrescenta o numero  de arestas
    G->E++;
    #ifdef DEBUG2
    printf("\nAdicionar aresta:  Aresta adicionada com sucesso\n");
    #endif
}

//Cria novo vertice
Node* criar_vertice (int v, Node *lista, int anterior){
    Node *novo = (Node *)malloc(sizeof(Node));
    novo->id = v;
    novo->proximo = lista;
    novo->anterior = anterior;
    return novo;
}
void remover_aresta (Graph *G, int u, int v){
    Node *aux;
    Node *remove;
    #ifdef DEBUG2
    printf("\nRemover aresta: Removendo aresta %d -> %d", u, v);
    #endif
    //Remove o peso na matriz de adjacencias
    G->matrixadj[u-1][v] = 0;
    //Remove o numero  de arestas
    G->E--;
    for (aux = G->listadj[u-1]; aux != NULL; aux = aux->proximo){
        if (aux->proximo->id == v){
            #ifdef DEBUG2
            printf("\nRemovendo aresta:  Aresta removida da lista de adjacencia!");
            #endif
            remove = aux->proximo;
            aux->proximo = NULL;
            free(remove);
            return;
        }
    }
    #ifdef DEBUG2
    printf("\nRemover aresta:  Aresta removida com sucesso\n");
    #endif
}

int retorna_direcao(int origemX, int origemY, int destinoX, int destinoY){
    printf("\nRetorna direcao X %d Y %d Destino X %d Y %d\n", origemX, origemY, destinoX, destinoY);
    //Acima
    if(origemX < destinoX){
        //Noroeste
        if(origemY > destinoY){
            //printf("\nNoroeste\n");
            return NO;
        }//Nordeste
        else if(origemY < destinoY){
            //printf("\nNordeste\n");
            return NE;
        }//Norte
        else{
            //printf("\nNorte\n");
            return NN;
        }
    }//Abaixo
    else if(origemX > destinoX){
        //Sudoeste
        if(origemY > destinoY){
            //printf("\nSudoeste\n");
            return SO;
        }//Sudeste
        else if(origemY < destinoY){
            //printf("\nSudeste\n");
            return SE;
        }//Sul
        else{
            //printf("\nSul\n");
            return SS;
        }
    }//Laterais
    else {
        //Oeste
        if(origemY > destinoY){
            //printf("\nOeste\n");
            return OO;
        }//Leste
        else{
            //printf("\nLeste\n");
            return LL;
        }
    }
}
void construir_prio(int* prio, int direcao){
    //Direcoes e numeros  foram baseados no numpad do teclado
    int ciclo_adjacente [17] = {7, 4, 1, 2, 3, 6, 9, 8, 7, 4, 1, 2, 3, 6, 9, 8, 7};
    int leitor = 4;
    //Procura a direcao no array de adjacencias
    while(direcao != ciclo_adjacente[leitor]){
        leitor++;
    }
    prio[0] = ciclo_adjacente[leitor];
    prio[1] = ciclo_adjacente[leitor+1];
    prio[2] = ciclo_adjacente[leitor-1];
    prio[3] = ciclo_adjacente[leitor+2];
    prio[4] = ciclo_adjacente[leitor-2];
    prio[5] = ciclo_adjacente[leitor+3];
    prio[6] = ciclo_adjacente[leitor-3];
    prio[7] = ciclo_adjacente[leitor+4];
    //#ifdef DEBUG
    int i = 0;
    int  dir_NN, dir_NO, dir_NE, dir_OO, dir_LL, dir_SE, dir_SO, dir_SS = 0;
    printf("\nPrioridades da direcao leitor base (%d):\n", leitor);
    for(i = 0;i<8;i++){
        printf("%d, ", prio[i]);
        switch(prio[i])
        {
            case NE:
                dir_NE = i;
            break;
            case NN:
                dir_NN = i;
            break;
            case NO:
                dir_NO = i;
            break;
            case OO:
                dir_OO = i;
            break;
            case LL:
                dir_LL = i;
            break;
            case SS:
                dir_SS = i;
            break;
            case SE:
                dir_SE = i;
            break;
            case SO:
                dir_SO = i;
            break;
        }
    }
    printf("\n%d %d %d\n", dir_NO, dir_NN, dir_NE);
    printf("%d X %d\n", dir_OO, dir_LL);
    printf("%d %d %d\n", dir_SO, dir_SS, dir_SE);
    //#endif
}

void busca_best_choice(Graph *G, int** vertice, int atual_X, int atual_Y, int fin_posX, int fin_posY, int passo, int anterior, int direcao_anterior){
    if(atual_X >= 0 && atual_X <= G->M && atual_Y >= 0 && atual_Y <= G->N){
        printf("\nRecebendo: %d (%d,%d) passos %d anterior %d, ajuste de tentativa %d\n", vertice[atual_X][atual_Y], atual_X, atual_Y, passo, anterior, direcao_anterior);
    }
    if(atual_X == fin_posX && atual_Y == fin_posY){//Chegou ao destino
        printf("\nFim do grafo\n");
        print_grafo(G);
        return;
    }
    else if(G->limite_grafo == passo){//Chegou ao limite
        printf("\nChegou no limite de passos %d %d\n", G->limite_grafo, passo);
        return;
    }
    print_grafo(G);
    //Ajusta a escolha do proximo no BestChoice
    if(G->direcao_destino != retorna_direcao(G->M-atual_X, atual_Y, G->M-fin_posX, fin_posY)){
        G->direcao_destino = retorna_direcao(G->M-atual_X, atual_Y, G->M-fin_posX, fin_posY);
        construir_prio(G->prio, G->direcao_destino);
    }
    int tentativa = 0;
    if(anterior == vertice[atual_X][atual_Y]){//Verifica se e um retorno ao anterior e verifica somente as outras posicoes
        tentativa = direcao_anterior;
        anterior = G->listadj[vertice[atual_X][atual_Y]-1]->anterior;//ajusta o anterior ao anterior daquele vertice
    }
    int direcao = G->prio[tentativa];
    int chamou = 0;
    //printf("\nRetorno %d %d\n",vertice[atual_X][atual_Y], G->visitados[vertice[atual_X][atual_Y]]);
    while(tentativa < 8 && chamou == 0){
        printf("\nTentativa %d posicao %d passo atual %d\n", tentativa, direcao, passo);
        switch(direcao){
            case NO:
                if(atual_X-1 >= 0 && atual_X-1 < G->M && atual_Y-1 >= 0 && atual_Y-1 < G->N){
                    printf("\nProcurando por Noroeste %d id %d (%d,%d)\n", NO, vertice[atual_X-1][atual_Y-1], atual_X-1, atual_Y-1);
                    if(vertice[atual_X-1][atual_Y-1] > 0 && vertice[atual_X-1][atual_Y-1] != NULL && G->visitados[vertice[atual_X-1][atual_Y-1]] == 0){
                        if(vertice[atual_X-1][atual_Y-1] != anterior){
                            adicionar_aresta(G,vertice[atual_X][atual_Y], vertice[atual_X-1][atual_Y-1], anterior);
                            printf("\nSucesso\n");
                            passo++;
                            anterior = vertice[atual_X][atual_Y];
                            G->visitados[anterior] = 1;
                        }
                        else{

                            printf("\nRetorno %d %d\n",anterior, G->visitados[anterior]);
                            passo--;
                        }
                        busca_best_choice(G, vertice, atual_X-1, atual_Y-1, fin_posX, fin_posY, passo, anterior, direcao_oposta(G->prio, NO)+1);
                        chamou = 1;
                    }
                    else{
                        printf("Impossivel\n");
                    }
                }
            break;
            case NN:
                if(atual_X-1 >= 0 && atual_X-1 < G->M && atual_Y >= 0 && atual_Y < G->N){
                    printf("\nProcurando por Norte %d id %d (%d,%d)\n", NN, vertice[atual_X-1][atual_Y], atual_X-1, atual_Y);
                    if(vertice[atual_X-1][atual_Y] > 0 && vertice[atual_X-1][atual_Y] != NULL && G->visitados[vertice[atual_X-1][atual_Y]] == 0){
                        if(vertice[atual_X-1][atual_Y] != anterior){
                            adicionar_aresta(G,vertice[atual_X][atual_Y], vertice[atual_X-1][atual_Y], anterior);
                            printf("\nSucesso\n");
                            passo++;
                            anterior = vertice[atual_X][atual_Y];
                            G->visitados[anterior] = 1;
                        }else{

                            printf("\nRetorno %d %d\n",anterior, G->visitados[anterior]);
                            passo--;
                        }
                        busca_best_choice(G, vertice, atual_X-1, atual_Y, fin_posX, fin_posY, passo, anterior, direcao_oposta(G->prio, NN)+1);
                        chamou = 1;
                    }
                    else{
                        printf("Impossivel\n");
                    }
                }
            break;
            case NE:
                if(atual_X-1 >= 0 && atual_X-1 < G->M && atual_Y+1 >= 0 && atual_Y+1 < G->N){
                    printf("\nProcurando por Nordeste %d id %d (%d,%d)\n", NE, vertice[atual_X-1][atual_Y+1], atual_X-1, atual_Y+1);
                    if(vertice[atual_X-1][atual_Y+1] > 0 && vertice[atual_X-1][atual_Y+1] != NULL && G->visitados[vertice[atual_X-1][atual_Y+1]] == 0){
                        if(vertice[atual_X-1][atual_Y+1] != anterior){
                            adicionar_aresta(G,vertice[atual_X][atual_Y], vertice[atual_X-1][atual_Y+1], anterior);
                            printf("\nSucesso\n");
                            passo++;
                            anterior = vertice[atual_X][atual_Y];
                            G->visitados[anterior] = 1;
                        }else{

                            printf("\nRetorno %d %d\n", anterior, G->visitados[anterior]);
                            passo--;
                        }
                        busca_best_choice(G, vertice, atual_X-1, atual_Y+1, fin_posX, fin_posY, passo, anterior, direcao_oposta(G->prio, NE)+1);
                        chamou = 1;
                    }
                    else{
                        printf("Impossivel\n");
                    }
                }
            break;
            case OO:
                if(atual_X >= 0 && atual_X < G->M && atual_Y-1 >= 0 && atual_Y-1 < G->N){
                    printf("\nProcurando por Oeste %d id %d (%d,%d)\n", OO, vertice[atual_X][atual_Y-1], atual_X, atual_Y-1);
                    if(vertice[atual_X][atual_Y-1] > 0 && vertice[atual_X][atual_Y-1] != NULL && G->visitados[vertice[atual_X][atual_Y-1]] == 0){
                        if(vertice[atual_X][atual_Y-1] != anterior){
                            adicionar_aresta(G,vertice[atual_X][atual_Y], vertice[atual_X][atual_Y-1], anterior);
                            printf("\nSucesso\n");
                            passo++;
                            anterior = vertice[atual_X][atual_Y];
                            G->visitados[anterior] = 1;
                        }else{

                            printf("\nRetorno %d %d\n", anterior, G->visitados[anterior]);
                            passo--;
                        }
                        busca_best_choice(G, vertice, atual_X, atual_Y-1, fin_posX, fin_posY, passo, anterior, direcao_oposta(G->prio, OO)+1);
                        chamou = 1;
                    }
                    else{
                        printf("Impossivel\n");
                    }
                }
            break;
            case LL:
                if(atual_X >= 0 && atual_X < G->M && atual_Y+1 >= 0 && atual_Y+1 < G->N){
                    printf("\nProcurando por Leste %d id %d (%d,%d)\n", LL, vertice[atual_X][atual_Y+1], atual_X, atual_Y+1);
                    if(vertice[atual_X][atual_Y+1] > 0 && vertice[atual_X][atual_Y+1] != NULL && G->visitados[vertice[atual_X][atual_Y+1]] == 0){
                        if(vertice[atual_X][atual_Y+1] != anterior){
                            adicionar_aresta(G,vertice[atual_X][atual_Y], vertice[atual_X][atual_Y+1], anterior);
                            printf("\nSucesso\n");
                            passo++;
                            anterior = vertice[atual_X][atual_Y];
                            G->visitados[anterior] = 1;
                        }else{

                            printf("\nRetorno %d %d\n", anterior, G->visitados[anterior]);
                            passo--;
                        }
                        busca_best_choice(G, vertice, atual_X, atual_Y+1, fin_posX, fin_posY, passo, anterior, direcao_oposta(G->prio, LL)+1);
                        chamou = 1;
                    }
                    else{
                        printf("Impossivel\n");
                    }
                }
            break;
            case SO:
                if(atual_X+1 >= 0 && atual_X+1 < G->M && atual_Y-1 >= 0 && atual_Y-1 < G->N){
                    printf("\nProcurando por Sudoeste %d id %d (%d,%d)\n", SO, vertice[atual_X+1][atual_Y-1], atual_X+1, atual_Y-1);
                    if(vertice[atual_X+1][atual_Y-1] > 0 && vertice[atual_X+1][atual_Y-1] != NULL && G->visitados[vertice[atual_X+1][atual_Y-1]] == 0){
                        if(vertice[atual_X+1][atual_Y-1] != anterior){
                            adicionar_aresta(G,vertice[atual_X][atual_Y], vertice[atual_X+1][atual_Y-1], anterior);
                            printf("\nSucesso\n");
                            passo++;
                            anterior = vertice[atual_X][atual_Y];
                            G->visitados[anterior] = 1;
                        }else{

                            printf("\nRetorno %d %d\n", anterior, G->visitados[anterior]);
                            passo--;
                        }
                        busca_best_choice(G, vertice, atual_X+1, atual_Y-1, fin_posX, fin_posY, passo, anterior, direcao_oposta(G->prio, SO)+1);
                        chamou = 1;
                    }
                    else{
                        printf("Impossivel\n");
                    }
                }

            break;
            case SS:
                if(atual_X+1 >= 0 && atual_X+1 < G->M && atual_Y >= 0 && atual_Y < G->N){
                    printf("\nProcurando por Sul %d id %d (%d,%d)\n", SS, vertice[atual_X+1][atual_Y], atual_X+1, atual_Y);
                    if(vertice[atual_X+1][atual_Y] > 0 && vertice[atual_X+1][atual_Y] != NULL && G->visitados[vertice[atual_X+1][atual_Y]] == 0){
                        if(vertice[atual_X+1][atual_Y] != anterior){
                            adicionar_aresta(G,vertice[atual_X][atual_Y], vertice[atual_X+1][atual_Y], anterior);
                            printf("\nSucesso\n");
                            passo++;
                            anterior = vertice[atual_X][atual_Y];
                            G->visitados[anterior] = 1;
                        }else{

                            printf("\nRetorno %d %d\n", anterior, G->visitados[anterior]);
                            passo--;
                        }
                        busca_best_choice(G, vertice, atual_X+1, atual_Y, fin_posX, fin_posY, passo, anterior, direcao_oposta(G->prio, SS)+1);
                        chamou = 1;
                    }
                    else{
                        printf("Impossivel\n");
                    }
                }
            break;
            case SE:
                if(atual_X+1 >= 0 && atual_X+1 < G->M && atual_Y+1 >= 0 && atual_Y+1 < G->N){
                    printf("\nProcurando por Sudeste %d id %d (%d,%d)\n", SE, vertice[atual_X+1][atual_Y+1], atual_X+1, atual_Y+1);
                    if(vertice[atual_X+1][atual_Y+1] > 0 && vertice[atual_X+1][atual_Y+1] != NULL && G->visitados[vertice[atual_X+1][atual_Y+1]] == 0){
                        if(vertice[atual_X+1][atual_Y+1] != anterior){
                            adicionar_aresta(G,vertice[atual_X][atual_Y], vertice[atual_X+1][atual_Y+1], anterior);
                            printf("\nSucesso\n");
                            passo++;
                            anterior = vertice[atual_X][atual_Y];
                            G->visitados[anterior] = 1;
                        }else{

                            printf("\nRetorno %d %d\n", anterior, G->visitados[anterior]);
                            passo--;
                        }
                        busca_best_choice(G, vertice, atual_X+1, atual_Y+1, fin_posX, fin_posY, passo, anterior, direcao_oposta(G->prio, SE)+1);
                        chamou = 1;
                    }
                    else{
                        printf("Impossivel\n");
                    }
                }
            break;
            default:
                printf("Erro\n");

        }
        tentativa++;
        direcao = G->prio[tentativa];
        if(tentativa > 7){
            chamou = 1;
            break;
        }
    }
    //No com vizinhos esgotados
    if(tentativa > 7){
        printf("\nTestou todos as possibilidades!\n");
    }
}
void print_grafo(Graph *G){
    struct node *aux;
    int i;
    printf("\nImprimindo grafo:\n");
    for(i=0;i < G->V;i++){
        aux = G->listadj[i];
        if(aux != NULL){
            printf("\n%d - ", i+1);
        }
        while(aux != NULL){
            printf("%d -> %d ", i+1, aux->id);
            aux = aux->proximo;
        }
    }
    printf("\n");
}
int direcao_oposta(int* prio, int direcao){
    int oposto;
    switch(direcao){
        case NN:
            oposto = SS;
        break;
        case SS:
            oposto = NN;
        break;
        case NO:
            oposto = SE;
        break;
        case SE:
            oposto = NO;
        break;
        case NE:
            oposto = SO;
        break;
        case SO:
            oposto = NE;
        break;
        case LL:
            oposto = OO;
        break;
        case OO:
            oposto = LL;
        break;
    }
    //printf("\nDirecao fornecida %d", direcao);
    //printf("\nDirecao oposta %d", oposto);
    int posicao = 0;
    while(oposto != prio[posicao]){
        posicao++;
        //printf("\n%d prio %d", posicao, prio[posicao]);
        if(posicao > 7){
            printf("Erro!");
            break;
        }
    }
    //printf("\nPosicao %d", posicao);
    return posicao;
}
