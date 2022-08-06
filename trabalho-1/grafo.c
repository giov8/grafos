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
/* Função que percorre o grafo g e verifica se ele é k regular
   devolve 1 se g é k-regular, ou 0 caso contrário */
int k_regular(grafo g, int k) {
  
  if (!g) {
    fprintf(stderr, "Erro: não há grafo em memória.\n");
    exit(-2);    
  }

  vertice v;

  // Percorre os vértices para verificar k-regularidade
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
int completo(grafo g) {
  
  if (!g) {
    fprintf(stderr, "Erro: não há grafo em memória.\n");
    exit(-2);    
  }

  int n = n_vertices(g);

  // se for grafo trivial, é conexo
  if (n == 1)
    return 1;

  // O número de arestas em um grafo completo é n(n-1)/2.
  if (n_arestas(g) == ( (n * (n-1)) / 2) )
    return 1;

  return 0;
}

// -----------------------------------------------------------------------------
/* Verifica se os vertices u e v são vizinhos em g
   retorna 1 caso forem vizinhos, 0 caso contrário */

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
/* Adiciona um vertice v ao conjunto*/
void adiciona_ao_conjunto(vertice v, vertice **conjunto, int *tam) {
  printf("add ao conjundo\n");

  if (!v) {
  fprintf(stderr, "Erro: vértice inválido.\n");
  exit(-3);    
  }

  if (!conjunto) {
  fprintf(stderr, "Erro: conjunto inválido.\n");
  exit(-4);    
  }

  printf("aqui\n");
  
  printf("antes de atribuir\n");
  conjunto[*tam] = v;
  printf("TAM ANTES %d\n", *tam);
  *tam += 1;
  printf("TAM DEPOIS %d\n", *tam);
  printf("add ao conjundo -- saiu\n");
}

// -----------------------------------------------------------------------------
/* Verifica se um vertice v está contido em um conjunto de tamanho tam*/
int contido_no_conjunto(vertice v, vertice *conjunto, int tam) {
  printf("contido conjundo\n");

  if (!v) {
  fprintf(stderr, "Erro: vértice inválido.\n");
  exit(-3);    
  }

  if (!conjunto) {
  fprintf(stderr, "Erro: conjunto inválido.\n");
  exit(-4);    
  }

  // Procura no conjunto pelo vértice
  for (int i = 0; i < tam; i++)
    if (v == conjunto[i])
      return 1;
  
  printf("contido conjundo ---saiu\n");
  return 0;
}

// -----------------------------------------------------------------------------
void visita(grafo g, vertice v, vertice **visitado, int *visitado_tam) {

  if (!g) {
    fprintf(stderr, "Erro: não há grafo em memória.\n");
    exit(-2);    
  }
  
  if (!v) {
  fprintf(stderr, "Erro: vértice inválido.\n");
  exit(-3);    
  }

  if (!visitado) {
  fprintf(stderr, "Erro: conjunto inválido.\n");
  exit(-4);    
  }

  printf("visita\n");
  adiciona_ao_conjunto(v, visitado, visitado_tam);

  // percorre vértices e verifica se é vizinho
  for (vertice u = agnxtnode(g, v); u; u = agnxtnode(g, u))
     if (vizinho(g, u, v))
      if (!contido_no_conjunto(u, *visitado, *visitado_tam))
        visita(g, u, visitado, visitado_tam); 
  printf("visita --saiu\n");    
}

// -----------------------------------------------------------------------------
int conexo(grafo g) {

  if (!g) {
    fprintf(stderr, "Erro: não há grafo em memória.\n");
    exit(-2);    
  }

  int n = n_vertices(g);
  vertice v, *visitado;
  int *visitado_tam;

  visitado = (vertice *) malloc((size_t) n * sizeof(vertice));
  *visitado_tam = 0;

  printf("1\n");
  // zera todos os elementos do conjunto visitado
  for (int i = 0; i < n; i++) visitado[i] = NULL;

  printf("2\n");
  // faz uma visita pelos vértices
  v = agfstnode(g);
  visita(g, v, &visitado, visitado_tam);

  printf("3\n");

  // se nem todos os vertices não foram visitados
  printf("visitado tam: %d", *visitado_tam);
  if (visitado_tam < n+1)
    return 0;

  return 1;
}

// -----------------------------------------------------------------------------
int bipartido(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int n_triangulos(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int **matriz_adjacencia(grafo g) {
  
  return NULL;
}

// -----------------------------------------------------------------------------
grafo complemento(grafo g) {
  
  return NULL;
}