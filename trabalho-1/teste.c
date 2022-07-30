#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void) {

  int num_v, num_a, g_max, g_min, g_medio;

  grafo g = le_grafo();
  printf("O grafo foi lido corretamente e tem:\n");

  num_v = n_vertices(g);
  printf("\t %d vértices;\n", num_v);

  num_a = n_arestas(g);
  printf("\t %d arestas;\n", num_a);

  g_max = grau_maximo(g);
  printf("\t grau máximo igual a %d;\n", g_max);

  g_min = grau_minimo(g);
  printf("\t grau mínimo igual a %d;\n", g_min);

  g_medio = grau_medio(g);
  printf("\t grau médio igual a %d.\n\n", g_medio);
    
  escreve_grafo(g);
  destroi_grafo(g);

  return 0;
}