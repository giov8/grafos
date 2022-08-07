//*******************************************
//   Grafos:  Trabalho 1 - 2022.1           *
//   Curso:   Informática Biomédica - UFPR  *
//   Alunos:  Giovani G. Marciniak          *
//            Marisa Sel Franco             *
//*******************************************

#include <stdio.h>
#include "grafo.h"
#include <stdlib.h>
#include <graphviz/cgraph.h>

typedef Agedge_t *aresta;

//------------------------------------------------------------------------------
grafo le_grafo(void) {

  grafo g = agread(stdin, NULL);

  if (!g) {
    fprintf(stderr, "Erro: não foi possível ler o grafo.\n");
    exit(-1);
  }

  return g; 
}

//------------------------------------------------------------------------------
void destroi_grafo(grafo g) {
  
  if (!g) {
    fprintf(stderr, "Erro: não há grafo em memória.\n");
    exit(-2);
  }
  agfree(g, NULL);
}
//------------------------------------------------------------------------------
grafo escreve_grafo(grafo g) {
  
  if (!g) {
    fprintf(stderr, "Erro: não há grafo em memória.\n");
    exit(-2);
  }
  agwrite(g, stdout);

  return g;
}

// -----------------------------------------------------------------------------
int n_vertices(grafo g) {
  
  int num_vertices;

  if (!g) {
    fprintf(stderr, "Erro: não há grafo em memória.\n");
    exit(-2);    
  }
  num_vertices = agnnodes(g);

  return num_vertices;
}
// -----------------------------------------------------------------------------
int n_arestas(grafo g) {

  int num_arestas;

  if (!g) {
    fprintf(stderr, "Erro: não há grafo em memória.\n");
    exit(-2);    
  }
  num_arestas = agnedges(g);

  return num_arestas;
}

// -----------------------------------------------------------------------------
int grau(vertice v, grafo g) {

  int grau_vertice;

  if (!g) {
    fprintf(stderr, "Erro: não há grafo em memória.\n");
    exit(-2);    
  }  
  if (!v) {
    fprintf(stderr, "Erro: vértice inválido.\n");
    exit(-3);    
  }
  grau_vertice = agdegree(g, v, TRUE, TRUE);    // conta tanto arestas de entrada quanto de saída

  return grau_vertice;
}

// -----------------------------------------------------------------------------
int grau_maximo(grafo g)  {

  vertice v;
  int grau_vertice, maior_grau;

  if (!g) {
    fprintf(stderr, "Erro: não há grafo em memória.\n");
    exit(-2);    
  }

  maior_grau = grau(agfstnode(g),g);           // chuta que o 1º vértice tem o maior grau

  // laço que percorre os vértices para calcular o grau máximo
  for (v = agfstnode(g); v; v = agnxtnode(g, v)) {
    grau_vertice = grau(v, g);
    if (grau_vertice > maior_grau)
      maior_grau = grau_vertice;    
  }

  return maior_grau;
}

// -----------------------------------------------------------------------------
int grau_minimo(grafo g)  {

  vertice v;
  int grau_vertice, menor_grau;

  if (!g) {
    fprintf(stderr, "Erro: não há grafo em memória.\n");
    exit(-2);    
  }

  menor_grau = grau(agfstnode(g), g);           // chuta que o 1º vértice tem o menor grau

  // laço que percorre os vértices para calcular o grau mínimo
  for (v = agfstnode(g); v; v = agnxtnode(g, v)) {
    grau_vertice = grau(v, g);
    if (grau_vertice < menor_grau)
      menor_grau = grau_vertice;    
  }

  return menor_grau;
}

// -----------------------------------------------------------------------------
int grau_medio(grafo g) {

  vertice v;
  int somatorio_graus = 0, grau_medio;

  if (!g) {
    fprintf(stderr, "Erro: não há grafo em memória.\n");
    exit(-2);    
  }

  // laço que percorre os vértices para fazer o somatório dos graus
  for (v = agfstnode(g); v; v = agnxtnode(g, v))
    somatorio_graus += grau(v, g);
  grau_medio = somatorio_graus / n_vertices(g); // calcula o grau médio de g

  return grau_medio;
}

// -----------------------------------------------------------------------------
/* Função que percorre o grafo G e verifica se ele é k-regular:
   devolve 1 se G é k-regular e 0 caso contrário */
int k_regular(grafo g, int k) {
  
  if (!g) {
    fprintf(stderr, "Erro: não há grafo em memória.\n");
    exit(-2);    
  }

  vertice v;

  // percorre os vértices para verificar k-regularidade
  for (v = agfstnode(g); v; v = agnxtnode(g, v))
    if (grau(v, g) != k)
      return 0;

  return 1;
}

// -----------------------------------------------------------------------------
int regular(grafo g) {

  if (!g) {
    fprintf(stderr, "Erro: não há grafo em memória.\n");
    exit(-2);    
  }

  vertice v = agfstnode(g);
  int k = grau(v, g);

  return k_regular(g, k);
}

// -----------------------------------------------------------------------------
/* Função que verifica se o grafo G é completo, ou seja, se E(G) = n(n-1)/2:
   devolve 1 se G é completo e 0 caso contrário */
int completo(grafo g) {
  
  if (!g) {
    fprintf(stderr, "Erro: não há grafo em memória.\n");
    exit(-2);    
  }

  int n = n_vertices(g);

  // se for grafo trivial, é completo
  if (n == 1)
    return 1;

  // o número de arestas em um grafo completo é n(n-1)/2.
  if (n_arestas(g) == ( (n * (n-1)) / 2) )
    return 1;

  return 0;
}

// -----------------------------------------------------------------------------
/* Verifica se os vértices u e v são vizinhos em G:
   retorna 1 caso forem vizinhos e 0 caso contrário */
int vizinho(grafo g, vertice u, vertice v) {

  if (!g) {
    fprintf(stderr, "Erro: não há grafo em memória.\n");
    exit(-2);    
  }
  
  if (!v || !u) {
    fprintf(stderr, "Erro: vértice inválido.\n");
    exit(-3);    
  }

  if (agedge(g, u, v, NULL, 0))
    return 1;
  
  return 0; 
}

// -----------------------------------------------------------------------------
/* Verifica se um vértice v está contido em um conjunto de tamanho tam:
   retorna 1 caso v esteja contido no conjunto e 0 caso contrário */
int contido_no_conjunto(vertice v, vertice conjunto[], int tam) {

  if (!v) {
    fprintf(stderr, "Erro: vértice inválido.\n");
    exit(-3);    
  }

  if (!conjunto) {
    fprintf(stderr, "Erro: conjunto inválido.\n");
    exit(-4);    
  }

  // procura pelo vértice no conjunto de interesse
  for (int i = 0; i < tam; i++)
    if (v == conjunto[i])
      return 1;
  
  return 0;
}

// -----------------------------------------------------------------------------
/* Verifica se um grafo G é conexo usando uma busca em profundidade(DFS):
   retorna 1 caso seja e 0 caso contrário */
int conexo(grafo g) {

  if (!g) {
    fprintf(stderr, "Erro: não há grafo em memória.\n");
    exit(-2);    
  }

  int n = n_vertices(g);
  vertice v, visitado[n], pilha[n];
  int visitado_tam, pilha_tam, n_vizinhos;

  pilha[0] = agfstnode(g);
  pilha_tam = 1;
  visitado_tam = 0;
  n_vizinhos = 0;

  while (pilha_tam != 0) {
    pilha_tam--;
    v = pilha[pilha_tam];

    if (!contido_no_conjunto(v, visitado, visitado_tam)) {
      for (vertice u = agnxtnode(g, v); u; u = agnxtnode(g, u))
        if (vizinho(g, u, v))
          if (!contido_no_conjunto(u, visitado, visitado_tam)) {
            pilha[pilha_tam] = u;
            pilha_tam++;
            n_vizinhos++;
          }
    }

    visitado[visitado_tam] = v;
    visitado_tam++;
  }

  if (n_vizinhos == n-1)
    return 1;
  
  return 0;
}

// -----------------------------------------------------------------------------
/* Verifica se um grafo G é bipartido usando uma busca em profundidade(DFS)
   e colorindo os vértices: retorna 1 caso seja e 0 caso contrário */
int bipartido(grafo g) {

  if (!g) {
    fprintf(stderr, "Erro: não há grafo em memória.\n");
    exit(-2);    
  }
  
  int n = n_vertices(g);
  int pilha_tam = 0;

  // struct para associar vértice a cor
  typedef struct vertice_colorido {
    vertice v;
    int cor;
  } vertice_colorido;

  vertice_colorido vertices[n];
  vertice_colorido pilha[n];
  vertice_colorido u, v;

  // colore todos vértices de "branco" (representado pelo 0)
  int i = 0;
  for (vertice w = agfstnode(g); w; w = agnxtnode(g, w)) {
    vertices[i].v = w;
    vertices[i].cor = 0;
    i++;
  }

  for (i = 0; i < n; i++) {
    // se vértice for branco, pinta
    if (!vertices[i].cor) {
      vertices[i].cor = 1;
      pilha[pilha_tam] = vertices[i];
      pilha_tam++;
    }

    while (pilha_tam > 0) {
      pilha_tam--;
      v = pilha[pilha_tam];

      for (int j = 0; j < n; j++) {         
        // verifica vizinhos
        if (vizinho(g, vertices[j].v, v.v)) {
          if (!vertices[j].cor) {
            vertices[j].cor = (v.cor % 2) + 1;
            pilha[pilha_tam] = vertices[j];
            pilha_tam++;
          }
          else if (vertices[j].cor == v.cor) return 0;
        }
      }
    }
  }

  return 1;
}

// -----------------------------------------------------------------------------
/* Multiplica duas matrizes quadradas de tamanho n: devolve a matriz resultante */
int **multiplica_matrizes(int **matriz_a, int **matriz_b, int n) {

  if (!matriz_a || !matriz_b) {
    fprintf(stderr, "Erro: não há matriz adjacência em memória.\n");
    exit(-5);    
  }
  
  int **matriz_aux = malloc((size_t)n * sizeof(int*));
  for (int i = 0; i < n; i++)
    matriz_aux[i] = (int*) malloc((size_t)n * sizeof(int));

  if (!matriz_aux) {
    fprintf(stderr, "Erro: não foi possível alocar matriz auxiliar.\n");
    exit(-5);    
  }

  // faz a multiplicação das matrizes a e b e coloca o resultado na
  // na matriz auxiliar
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      matriz_aux[i][j] = 0;
      for (int k = 0; k < n; k++)
        matriz_aux[i][j] += matriz_a[i][k] * matriz_b[k][j];
    }
  }

  return matriz_aux;
}

// -----------------------------------------------------------------------------
/* Calcula o traço de uma matriz quadradada de tamanho n, ou seja, a soma dos 
   elementos de sua diagonal principal */
int calculaTraco(int **matriz, int n) {

  if (!matriz) {
    fprintf(stderr, "Erro: não foi possível calcular o traço porque não há matriz em memória.\n");
    exit(-5);    
  }

  int traco = 0;

  for (int i = 0; i < n; i++)
    traco += matriz[i][i];

  return traco;
}


// -----------------------------------------------------------------------------
/* Calcula a quantidade de cliques de tamanho 3 de um grafo G não-direcionado, ou seja, 
   calcula o número de triângulos de G. Retorna o número de triângulos do grafo */
int n_triangulos(grafo g) {
  
  if (!g) {
    fprintf(stderr, "Erro: não há grafo em memória.\n");
    exit(-2);    
  }

  int traco, num_cliques_3 = 0;
  int n = n_vertices(g);

  if (n < 3)
    return num_cliques_3;

  // calcula (matriz_adjacencia(g))³ com duas multiplicações sucessivas
  int **matriz_aux = multiplica_matrizes(matriz_adjacencia(g), matriz_adjacencia(g), n);
  matriz_aux = multiplica_matrizes(matriz_adjacencia(g), matriz_aux, n);

  // calcula o traço da (matriz_adjacencia(g))³ 
  traco = calculaTraco(matriz_aux, n);

  // calcula número de cliques de tamanho 3 do grafo G não-direcionado
  num_cliques_3 = traco / 6;

  // libera memória
  free(matriz_aux);

  return num_cliques_3;
}

// -----------------------------------------------------------------------------
/* Representa um grafo G por uma matriz de adjacência */
int **matriz_adjacencia(grafo g) {
  
  if (!g) {
    fprintf(stderr, "Erro: não há grafo em memória.\n");
    exit(-2);    
  }

  int n = n_vertices(g);
  int i, j;

  // alocação de memória
  int **matriz = malloc((size_t)n * sizeof(int*));
  for (i = 0; i < n; i++) {
    matriz[i] = (int*) malloc((size_t)n * sizeof(int));
  }

  i = 0;
  j = 0;

  for (vertice v = agfstnode(g); v; v = agnxtnode(g, v)) {
    j = 0;
    for (vertice u = agfstnode(g); u; u = agnxtnode(g, u)) {
      if (v == u) {
        matriz[i][j] = 0;
        j++;
        continue;
      }
      if (vizinho(g, u, v)) 
        matriz[i][j] = 1;
      else 
        matriz[i][j] = 0;  
      j++;
    }
    i++;
  }

  return matriz;
}

// -----------------------------------------------------------------------------
void imprimir_matriz_adjacencia(int **matriz, int n) {

  if (!matriz) {
    fprintf(stderr, "Erro: não há matriz adjacência em memória.\n");
    exit(-5);    
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      printf("%d ", matriz[i][j]);
    printf("\n");
  }

  return;
}

// -----------------------------------------------------------------------------
/* Devolve o grafo H que é complemento do grafo G, dado que tal V(H) = V(G)
   e dois vértices de H são adjacentes se e somente se eles não são adjacentes em G */
grafo complemento(grafo g) {

  if (!g) {
    fprintf(stderr, "Erro: não há grafo em memória.\n");
    exit(-2);    
  }

  grafo complemento = agopen("g-1", Agstrictundirected, NULL);
  vertice v, u;

  for (u = agfstnode(g); u; u = agnxtnode(g, u)) 
    agnode(complemento, agnameof(u), TRUE);
  
  for (u = agfstnode(g); u; u = agnxtnode(g, u)) {
    for (v = agnxtnode(g, u); v; v = agnxtnode(g, v)) {
      if (!vizinho(g, u, v))
        agedge(complemento, agnode(complemento, agnameof(u), FALSE), agnode(complemento, agnameof(v), FALSE), NULL, TRUE);      
    }
  }
  
  return complemento;
}