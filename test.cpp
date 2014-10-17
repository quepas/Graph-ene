#include <iostream>

#include "GraphInfo.h"
#include "AdjacencyMatrixGraph.h"

int main() {
  Graphene::AdjacencyMatrixGraph<int> graph;
  Graphene::PrintAdjacencyMatrix(graph);
}