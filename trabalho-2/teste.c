#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void) {

  grafo g = le_grafo();

  decompoe(g);
  printf("\nQuantidade de subgrafos: %d\n", agnsubg(g));
  escreve_grafo(g);

  destroi_grafo(g);

  return 0;
}