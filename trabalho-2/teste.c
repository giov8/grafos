#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void) {

  grafo g = le_grafo();

  decompoe(g);

  escreve_grafo(g);

  printf("\nQuantidade de subgrafos: %d\n", agnsubg(g));
  for (grafo sub = agfstsubg(g); sub; sub = agnxtsubg(sub))
    escreve_grafo(sub);

  destroi_grafo(g);

  return 0;
}