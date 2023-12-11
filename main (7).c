#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_QUEUE_SIZE 100

// Definição da estrutura para um nó da fila
struct QueueNode {
    int data1;
    int data2;
};

// Definição da estrutura da fila
struct Queue {
    struct QueueNode array[MAX_QUEUE_SIZE];
    int front, rear, size;
};

void createQueue(struct Queue* queue) {
    queue->size = 0;
    queue->front = 0;
    queue->rear = -1;
}

bool QueueisEmpty(struct Queue* queue) {
    return (queue->size == 0);
}

// Função para verificar se a fila está cheia
bool isFull(struct Queue* queue) {
    return (queue->size == MAX_QUEUE_SIZE);
}

// Função para enfileirar um elemento
void enqueue(struct Queue* queue, int data1, int data2) {
    if (isFull(queue)) {
        printf("A fila está cheia. Não é possível enfileirar.\n");
        return;
    }
    queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
    queue->array[queue->rear].data1 = data1;
    queue->array[queue->rear].data2 = data2;
    queue->size += 1;
}

// Função para desenfileirar um elemento
struct QueueNode dequeue(struct Queue* queue) {
    struct QueueNode emptyNode = { -1, -1 }; // Valor de sentinela para indicar fila vazia
    if (QueueisEmpty(queue)) {
        printf("A fila está vazia. Não é possível desenfileirar.\n");
        return emptyNode;
    }
    struct QueueNode item = queue->array[queue->front];
    queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
    queue->size -= 1;
    return item;
}

void printQueue(struct Queue* queue) {
    if (QueueisEmpty(queue)) {
        printf("A fila está vazia.\n");
        return;
    }

    printf("Elementos da fila: ");
    int i = queue->front;
    do {
        printf("(%d, %d) ", queue->array[i].data1, queue->array[i].data2);
        i = (i + 1) % MAX_QUEUE_SIZE;
    } while (i != (queue->rear + 1) % MAX_QUEUE_SIZE);
    printf("\n");
}

// Definindo a estrutura de um nó da lista de arestas
struct EdgeNode {
    int src;
    int dest;
    int weight;
    int circuito_mosquito;
    bool contaminated;
    struct EdgeNode* next;
};

// Definindo a estrutura de um vértice com uma lista de arestas
struct Vertex {
    struct EdgeNode* head;
};

// Função para adicionar uma aresta a um grafo não direcionado
void addEdge(struct Vertex graph[], int src, int dest, int weight, bool contaminated) {
    // Adiciona uma aresta da origem para o destino

    struct EdgeNode* newNode = (struct EdgeNode*)malloc(sizeof(struct EdgeNode));
    newNode->src = src;
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->contaminated = contaminated;
    newNode->circuito_mosquito = 0;
    newNode->next = graph[src].head;
    graph[src].head = newNode;

    // Adiciona a aresta do destino para a origem
    newNode = (struct EdgeNode*)malloc(sizeof(struct EdgeNode));
    newNode->src = dest;
    newNode->dest = src;
    newNode->weight = weight;
    newNode->contaminated = contaminated;
    newNode->next = graph[dest].head;
    graph[dest].head = newNode;
}

void printGraph(struct Vertex graph[], int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        struct EdgeNode* current = graph[i].head;
        printf("\nLista de adjacência do vértice %d:\n", i);
        while (current != NULL) {
            printf("  Origem: %d, Destino: %d, Peso: %d, Contaminado: %s\n",
                   current->src, current->dest, current->weight,
                   current->contaminated ? "true" : "false");
            current = current->next;
        }
        printf("\n");
    }
}


// Função para encontrar a aresta reversa
struct EdgeNode* findReverseEdge(struct Vertex graph[], int src, int dest, int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        struct EdgeNode* current = graph[i].head;
        while (current != NULL) {
            if (current->src == src && current->dest == dest) {

                return current;
            }
            current = current->next;
        }
    }
    return NULL; // Se não encontrar a aresta reversa
}

// Função para marcar a aresta reversa como contaminada
void markReverseContaminated(struct Vertex graph[], int src, int dest, int numVertices) {
    // Encontra a aresta reversa na lista (se existir)
    struct EdgeNode* reverseEdge = findReverseEdge(graph, dest, src, numVertices);

    // Marca a aresta reversa como contaminada
    if (reverseEdge != NULL) {
        reverseEdge->contaminated = true;
    }
}

// Função para imprimir as arestas contaminadas e marcar a aresta reversa como contaminada
void markReverseContaminatedEdges(struct Vertex graph[], int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        struct EdgeNode* current = graph[i].head;
        while (current != NULL) {
            if (current->contaminated) {
                // Marca a aresta reversa como contaminada
                markReverseContaminated(graph, i, current->dest, numVertices);
            }
            current = current->next;
        }
    }
}

// Função para diminuir a prioridade de um vértice na fila de prioridade
void diminuirPrioridade(struct Queue* fila, int novaPrioridade) {
    fila->array[fila->front].data2 = novaPrioridade;
}

// Função para encontrar a posição de um vértice na fila
int encontrarPosicao(struct Queue* fila, int vertice) {
    int posicao = -1;
    for (int i = fila->front; i != (fila->rear + 1) % MAX_QUEUE_SIZE; i = (i + 1) % MAX_QUEUE_SIZE) {
        if (fila->array[i].data1 == vertice) {
            posicao = i;
            break;
        }
    }
    return posicao;
}

// Função para verificar se um vértice está na fila
bool estaNaFila(struct Queue* fila, int vertice) {
    return (encontrarPosicao(fila, vertice) != -1);
}
bool todas_arestas_contaminadas(struct Vertex graph[], int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        struct EdgeNode* current = graph[i].head;
        while (current != NULL) {
            if (!current->contaminated) {
                // Se encontrar uma aresta não contaminada, retorna falso
                return false;
            }
            current = current->next;
        }
    }
    // Se todas as arestas foram contaminadas, retorna verdadeiro
    return true;
}

void marca_arestas_contaminadas(struct Vertex graph[], int ori, int numVertices) {
    struct EdgeNode* current = graph[ori].head;
    int distancia_mosquito_percorre = 100;
    struct Queue myQueue;
    createQueue(&myQueue);

    while (current != NULL) {
        current->contaminated = true;
        current->circuito_mosquito = distancia_mosquito_percorre - current->weight;
        enqueue(&myQueue, current->dest, current->circuito_mosquito);
        current = current->next;
    }

    struct QueueNode dequeuedNode;
    while (!QueueisEmpty(&myQueue)) {
        if(todas_arestas_contaminadas(graph, numVertices)){
           break;
        }
        dequeuedNode = dequeue(&myQueue);
        int u = dequeuedNode.data1;
        int v = dequeuedNode.data2;
        struct EdgeNode* temp = graph[u].head;
        while (temp != NULL) {
            if (v <= 0) break;
            temp->contaminated = true;
            temp->circuito_mosquito = v - temp->weight;
            enqueue(&myQueue, temp->dest, temp->circuito_mosquito);
            temp = temp->next;
        }
    }
    markReverseContaminatedEdges(graph, numVertices);
}

void printContaminatedEdges(struct EdgeNode* edges) {
    while (edges != NULL) {
        if (edges->contaminated) {
            printf("Origem: %d, Destino: %d, Peso: %d\n", edges->src, edges->dest, edges->weight);
        }
        edges = edges->next;
    }
}

struct Resultado {
    int* caminhoInvertido;
    int tamanhoCaminho;
    int distanciaTotal;
    int penultimoVertice;
    int ultimoVertice;
};


// Função para encontrar o menor caminho usando o algoritmo de Dijkstra
void dijkstra(struct Vertex graph[], int numVertices, int inicio, int destino, int* distancia, int* caminho) {
    // Inicializa a fila de prioridade como vazia
    struct Queue filaPrioridade;
    createQueue(&filaPrioridade);

    // Inicializa a distância do vértice de início como 0
    distancia[inicio] = 0;
    enqueue(&filaPrioridade, inicio, 0);

    // Loop principal do algoritmo de Dijkstra
    while (!QueueisEmpty(&filaPrioridade)) {
        struct QueueNode noAtual = dequeue(&filaPrioridade);
        int verticeAtual = noAtual.data1;
        int distAtual = noAtual.data2;

        // Percorre as arestas do vértice atual
        struct EdgeNode* current = graph[verticeAtual].head;
        while (current != NULL) {
            int novoPeso = distAtual + current->weight;

            // Se encontrarmos um caminho mais curto para um vizinho, atualizamos a distância
            if (novoPeso < distancia[current->dest]) {
                distancia[current->dest] = novoPeso;
                caminho[current->dest] = verticeAtual;
                enqueue(&filaPrioridade, current->dest, novoPeso);
            }

            current = current->next;
        }
    }
}


// Função para imprimir o caminho ao contrário usando uma pilha
int* imprimirCaminhoInvertido(int* caminho, int destino, int* tamanhoCaminho, int numVertices) {
    // Usar uma pilha para armazenar o caminho invertido
    int* pilha = (int*)malloc(numVertices * sizeof(int));
    int topo = -1;

    // Adicionar os vértices do caminho à pilha
    int verticeAtual = destino;
    while (verticeAtual != -1) {
        pilha[++topo] = verticeAtual;
        verticeAtual = caminho[verticeAtual];
    }

    // Criar um vetor para armazenar o caminho invertido
    int* caminhoInvertido = (int*)malloc((topo + 1) * sizeof(int));
    *tamanhoCaminho = topo + 1;

    // Preencher o vetor com os elementos do caminho invertido
    for (int i = 0; i <= topo; i++) {
        caminhoInvertido[i] = pilha[topo - i];
    }

    // Liberar memória alocada para a pilha
    free(pilha);

    // Retornar o vetor com os elementos do caminho invertido
    return caminhoInvertido;
}

struct Resultado encontrarCaminhoComNovoElemento(struct Vertex graph[], int numVertices, int inicio, int destino, int novoElemento) {
    // Inicializar arrays para armazenar distância e caminho para Dijkstra
    int* distancia = (int*)malloc(numVertices * sizeof(int));
    int* caminho = (int*)malloc(numVertices * sizeof(int));

    // Inicializar distância e caminho para Dijkstra
    for (int i = 0; i < numVertices; i++) {
        distancia[i] = INT_MAX;
        caminho[i] = -1;
    }

    // Executar o algoritmo de Dijkstra
    dijkstra(graph, numVertices, inicio, destino, distancia, caminho);

    // Chamar a função para obter o caminho invertido
    int tamanhoCaminho;
    int* caminhoInvertido = imprimirCaminhoInvertido(caminho, destino, &tamanhoCaminho, numVertices);

    // Adicionar um novo elemento ao vetor caminhoInvertido
    caminhoInvertido = (int*)realloc(caminhoInvertido, (tamanhoCaminho + 1) * sizeof(int));
    caminhoInvertido[tamanhoCaminho] = novoElemento;
    tamanhoCaminho++;

    // Calcular a distância total
    int distanciaTotal = distancia[destino];

    // Liberar memória alocada
    free(distancia);
    free(caminho);

    // Criar e retornar a estrutura de resultado
    struct Resultado resultado;
    resultado.caminhoInvertido = caminhoInvertido;
    resultado.tamanhoCaminho = tamanhoCaminho;
    resultado.distanciaTotal = distanciaTotal;

    return resultado;
}

// Função para processar uma aresta e armazenar origem e destino em uma estrutura
struct Resultado processarAresta(struct EdgeNode* aresta, int inicioDijkstra, struct Vertex graph[], int numVertices) {

    int destinoDijkstra = aresta->dest;

    // Chamar a função para encontrar o caminho invertido com um novo elemento
    struct Resultado resultado = encontrarCaminhoComNovoElemento(graph, numVertices, inicioDijkstra, destinoDijkstra, aresta->src);

    destinoDijkstra = aresta->src;

    // Chamar a função para encontrar o caminho invertido com um novo elemento
    struct Resultado resultado2 = encontrarCaminhoComNovoElemento(graph, numVertices, inicioDijkstra, destinoDijkstra, aresta->dest);

    resultado2.ultimoVertice = aresta->dest;
    resultado2.penultimoVertice = aresta->src;
    resultado2.distanciaTotal = resultado2.distanciaTotal + aresta->weight;
    resultado.ultimoVertice = aresta->src;
    resultado.penultimoVertice = aresta->dest;
    resultado.distanciaTotal = resultado.distanciaTotal + aresta->weight;
    if(resultado.distanciaTotal > resultado2.distanciaTotal) return resultado2;
    return resultado;
}

// Função para obter as arestas contaminadas de um grafo
struct EdgeNode* getContaminatedEdges(struct Vertex graph[], int numVertices) {
    struct EdgeNode* contaminatedEdges = NULL; // Inicializando como nulo

    for (int i = 0; i < numVertices; i++) {
        struct EdgeNode* current = graph[i].head;
        while (current != NULL) {
            if (current->contaminated) {
                // Adicionando a aresta contaminada ao vetor
                struct EdgeNode* newNode = (struct EdgeNode*)malloc(sizeof(struct EdgeNode));
                newNode->src = current->src;
                newNode->dest = current->dest;
                newNode->weight = current->weight;
                newNode->contaminated = current->contaminated;
                newNode->next = contaminatedEdges;
                contaminatedEdges = newNode;
            }
            current = current->next;
        }
    }

    return contaminatedEdges;
}

// Função para liberar a memória alocada para as arestas
void freeEdges(struct EdgeNode* edges) {
    while (edges != NULL) {
        struct EdgeNode* temp = edges;
        edges = edges->next;
        free(temp);
    }
}

// Função para remover uma aresta do grafo
void removeEdge(struct EdgeNode** headRef, int src, int dest) {
    struct EdgeNode* current = *headRef;
    struct EdgeNode* prev = NULL;

    // Procura a aresta a ser removida na lista
    while (current != NULL && (current->src != src || current->dest != dest)) {
        prev = current;
        current = current->next;
    }

    // Se a aresta foi encontrada, a remove da lista
    if (current != NULL) {
        if (prev != NULL) {
            prev->next = current->next;
        } else {
            *headRef = current->next;
        }

        free(current);
    }
}

// Função para encontrar o caminho mais curto que passa por todas as arestas contaminadas
void findShortestPathToContaminatedEdges(struct Vertex graph[], int numVertices, int src, struct EdgeNode* contaminatedEdges){
    struct Resultado resultado2;
    resultado2.distanciaTotal = INT_MAX;
    struct EdgeNode* contaminatedEdges2 = contaminatedEdges;
    struct Resultado resultado;
    while (contaminatedEdges != NULL) {
      // Função feita para encontrar o menor caminho até a aresta contaminada mais próxima
      struct Resultado resultado = processarAresta(contaminatedEdges, src, graph, numVertices);


        if(resultado.distanciaTotal < resultado2.distanciaTotal){
            resultado2 = resultado;
        }
        // Move para a próxima aresta contaminada
        contaminatedEdges = contaminatedEdges->next;
    }
    // Imprimir o caminho invertido
    printf("\nMenor Caminho:\n");
    for (int i = 0; i < resultado2.tamanhoCaminho; i++) {
        printf("%d ", resultado2.caminhoInvertido[i]);
    }

    int distanciaGlobal = resultado2.distanciaTotal;

    removeEdge(&contaminatedEdges2, resultado2.penultimoVertice, resultado2.ultimoVertice);
    removeEdge(&contaminatedEdges2, resultado2.ultimoVertice, resultado2.penultimoVertice);

    while(contaminatedEdges2 != NULL){
      int ultimoVerticeEntrada = resultado2.ultimoVertice;
      contaminatedEdges = contaminatedEdges2;

      resultado2.distanciaTotal = INT_MAX;
      while (contaminatedEdges != NULL) {

          resultado = processarAresta(contaminatedEdges, ultimoVerticeEntrada, graph, numVertices);

          if(resultado.distanciaTotal < resultado2.distanciaTotal){
              resultado2 = resultado;
          }
          // Move para a próxima aresta contaminada
          contaminatedEdges = contaminatedEdges->next;
      }
      // Imprimir o caminho invertido
      for (int i = 1; i < resultado2.tamanhoCaminho; i++) {
          printf("%d ", resultado2.caminhoInvertido[i]);
      }

      // Imprimir a distância total
      distanciaGlobal += resultado2.distanciaTotal; 
      removeEdge(&contaminatedEdges2, resultado2.penultimoVertice, resultado2.ultimoVertice);
      removeEdge(&contaminatedEdges2, resultado2.ultimoVertice, resultado2.penultimoVertice);
    }
    printf("\nDistancia Total: %d\n", distanciaGlobal);

}


int main() {
    int numVertices;
    printf("Digite o numero de vertices do grafo: ");
    scanf( "%d", &numVertices);

    // Criando um array de vértices
    struct Vertex graph[numVertices];

    // Inicializando as listas de arestas
    for (int i = 0; i < numVertices; i++) {
        graph[i].head = NULL;
    }

    // Adicionando arestas ao grafo bidirecionado
    int ori, dest, peso;

    printf("Digite os dados do grafo (origem, destino, distancia):\n");
    printf("Digite 0 0 0, para prosseguir!\n");
    while (1) {
        scanf(" %d %d %d", &ori, &dest, &peso);
        if (ori == 0 && dest == 0 && peso == 0) break;
        addEdge(graph, ori, dest, peso, false);
    }

    printf("===========================================================\n");
    printf("Grafo sem Contaminação:\n");
    printGraph(graph, numVertices);

    printf("===========================================================\n");
    printf("Digite os vértices que você quer contaminar:\n");
    printf("Digite -1 para prosseguir!\n");
    // Lendo arestas contaminadas
    while (1) {
        scanf("%d", &ori);
        if (ori == -1) break;
        marca_arestas_contaminadas(graph, ori, numVertices);
    }

    printf("===========================================================\n");
    printf("Grafo Contaminado:\n");
    printGraph(graph, numVertices);

    struct EdgeNode* contaminatedEdges = getContaminatedEdges(graph, numVertices);

    printf("===========================================================\n");
    printf("Arestas Contaminadas:\n");
    printContaminatedEdges(contaminatedEdges);

    int partida;
    printf("===========================================================\n");
    printf("De qual vértice o caminhão vai sair? ");
    scanf("%d", &partida);
    printf("===========================================================\n");
    findShortestPathToContaminatedEdges(graph, numVertices, partida, contaminatedEdges);


    return 0;
}

/*
Exemplo de entrada:

5

0 1 80
0 2 60
1 2 50
1 3 90
2 4 100
3 4 60
0 0 0

3
-1
*/