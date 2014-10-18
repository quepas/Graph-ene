#pragma once

#include "AdjacencyMatrixGraph.h"

#include <iostream>

namespace Graphene {

template <typename T>
void PrintAdjacencyMatrix(const AdjacencyMatrixGraph<T>& graph);

void PrintNodes(const std::vector<unsigned>& nodes);

template <typename T>
void PrintAdjacencyMatrix(const AdjacencyMatrixGraph<T>& graph)
{
  auto matrix = graph.matrix();
  for (auto& row : matrix) {
    for (auto& col : row) {
      std::cout << col << " ";
    }
    std::cout << std::endl;
  }
}

void PrintNodes(const std::vector<unsigned>& nodes)
{
  for (auto node : nodes) {
    std::cout << node << " ";
  }
  std::cout << std::endl;
}

}
// ~~ Graphene::GraphInfo