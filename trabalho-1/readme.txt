<h1>Implementação de uma biblioteca básica biblioteca para análise de grafos não-direcionados</h1>

Trabalho desenvolvido por Giovani G. Marciniak e Marisa Sel Franco, graduandos do curso de bacharelado em Informática Biomédica da UFPR, 
para a disciplina de CI165 - Algoritmos e Teoria dos Grafos, ministrada pelo prof. Dr. Renato Carmo, - conforme especificação disponível 
na [página da disciplina] (https://www.inf.ufpr.br/renato/ci1065/trabalho-1.html/). 

O objetivo era desenvolver uma biblioteca básica para análise de grafos em C, implementando no arquivo 
```
grafo.c
```
a especificação de
```
trabalho-1/grafo.h
```

O programa usa a linguagem de descrição de grafos dot, implementada pelo pacote de software GraphViz. O grafo é recebido pelo programa via 
entrada padrão. Parte das funções principais que compõem a biblioteca usou basicamente funções nativas do pacote graphviz para C encapsuladas
e, portanto, exigiu uma implementação bastante simples: 

- grafo le_grafo(void);
- void destroi_grafo(grafo g);
- grafo escreve_grafo(grafo g);
- int n_vertices(grafo g);
- int n_arestas(grafo g);
- int grau(vertice v, grafo g).

As demais funções exigiram o desenvolvimento de algoritmos mais complexos. Essas funções mais complexas também se utilizam de funções 
nativas do pacote graphviz para C e, em alguns casos, demandaram a criação de funções auxiliares para melhor modularização e organização
do código.

## Dependências:

:warning: [libgraphviz-dev](https://packages.debian.org/wheezy/libgraphviz-dev)
:warning: [graphviz](https://graphviz.org/download/)

## Como compilar
No terminal, execute: 

```
make
```

## Como rodar o programa de teste
No terminal, execute: 

```
./teste < <nome_arquivo.dot>
```

## Funções principais que compõem a biblioteca:

- grafo le_grafo(void)
Devolve o grafo lido da entrada padrão (formato dot).

- void destroi_grafo(grafo g)
Desaloca o grafo g.

- grafo escreve_grafo(grafo g)
Escreve g na saída padrão em formato dot e devolve g.

- int n_vertices(grafo g)
Devolve o número de vértices de g.

- int n_arestas(grafo g)
Devolve o número de arestas de g.

- int grau(vertice v, grafo g)
Devolve o grau do vértice v em g.

- int grau_maximo(grafo g)
Devolve o grau máximo de g.

- int grau_minimo(grafo g)
Devolve o grau mínimo de g.

- int grau_medio(grafo g)
Devolve o grau médio de g.

- int regular(grafo g)
Devolve 1 se g é regular e 0 caso contrário.

- int completo(grafo g)
Verifica se o grafo g é completo, ou seja, se E(G) = n(n-1)/2: devolve 1 se g é completo e 0 caso contrário.

- int conexo(grafo g)
Verifica se um grafo g é conexo usando uma busca em profundidade(DFS): devolve 1 se g é conexo e 0 caso contrário.

- int bipartido(grafo g)
Verifica se um grafo g é bipartido usando uma busca em profundidade(DFS) e colorindo os vértices: devolve 1 se g é bipartido e 0 caso contrário.

- int n_triangulos(grafo g)
Calcula o número de triângulos (subgrafos completos de 3 vértices ou quantidade de cliques de tamanho 3) em g (sendo g não-direcionado). 
A implementação realizada usa multiplicação de matrizes. É calculada a (matriz_adjacencia(g))³. A seguir, é feito o cálculo do traço da (matriz_adjacencia(g))³. 
Como o g é não-direcionado e são buscadas cliques de tamanho 3, o valor do traço é dividido por 6 (2 * 3). 
Devolve o número de triângulos de g. 

Obs. importante: apesar desta implementação para contar o número de triângulos de um grafo ser simples e relativamente rápida, para grafos grandes 
torna-se inviável, pois a complexidade de memória é da ordem de θ(n²), sendo n o número de vértices de g.

- int **matriz_adjacencia(grafo g)
Representa g por uma matriz de adjacência. Devolve uma matriz de adjacência de g onde as linhas/colunas estão ordenadas do mesmo modo 
que agfstnode() e agnxtnode() em libcgraph.

- void imprimir_matriz_adjacencia(int **matriz, int n)
Imprime na saída padrão a matriz de adjacência de g.

- grafo complemento(grafo g)
Devolve o grafo h que é complementar ao grafo g, dado que tal V(H) = V(G) e dois vértices de H são adjacentes se e somente se eles não são 
adjacentes em G.

## Funções auxiliares:

- int k_regular(grafo g, int k)
Percorre o grafo g e verifica se ele é k-regular: devolve 1 se g é k-regular e 0 caso contrário.

- int vizinho(grafo g, vertice u, vertice v)
Verifica se os vértices u e v são vizinhos em g: devolve 1 caso u e v sejam vizinhos em g e 0 caso contrário.

- int contido_no_conjunto(vertice v, vertice conjunto[], int tam)
Verifica se um vértice v está contido em um conjunto de tamanho tam: devolve 1 caso v esteja contido no conjunto e 0 caso contrário.

- int **multiplica_matrizes(int **matriz_a, int **matriz_b, int n)
Multiplica duas matrizes quadradas de tamanho n: devolve a matriz resultante.

- int calculaTraco(int **matriz, int n)
Calcula o traço de uma matriz quadradada de tamanho n, ou seja, a soma dos elementos de sua diagonal principal.

## Observações finais:

No momento da compilação do código usando o makefile, são exibidos alguns "warnings" devido às flags de compilação.
No entanto, nenhum deles afeta o funcionamento da biblioteca aparentemente.

Há comentários complementares ao longo do código que explicam de forma mais esmiuçada algumas das implementações de funções mais complexas.
