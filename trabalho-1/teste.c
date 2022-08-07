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
  printf("\t grau médio igual a %d.\n", g_medio);
    
  if (regular(g))
    printf("\t O grafo é regular.\n");
  else
    printf("\t O grafo NÃO é regular.\n");

  if (completo(g))
    printf("\t O grafo é completo.\n");
  else
    printf("\t O grafo NÃO é completo.\n");

  if (conexo(g))
    printf("\t O grafo é conexo.\n");
  else
    printf("\t O grafo NÃO é conexo.\n");

  if (bipartido(g))
    printf("\t O grafo é bipartido.\n");
  else
    printf("\t O grafo NÃO é bipartido.\n");

  printf("\nMatriz adjacencia: \n");
  imprimir_matriz_adjacencia(matriz_adjacencia(g), num_v);

  printf("\nComplemento: \n");
  imprimir_matriz_adjacencia(matriz_adjacencia(complemento(g)), num_v);

  printf("\n");
  escreve_grafo(g);
  destroi_grafo(g);

  return 0;
}