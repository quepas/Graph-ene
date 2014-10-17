#pragma once

#include "AdjacencyMatrixGraph.h"

#include <iostream>

namespace Graphene {

template <typename T>
void PrintAdjacencyMatrix(const AdjacencyMatrixGraph<T>& graph);

}

template <typename T>
void Graphene::PrintAdjacencyMatrix(const AdjacencyMatrixGraph<T>& graph)
{
  auto matrix = graph.matrix();
  for (auto& row : matrix) {
    for (auto& col : row) {
      std::cout << col << " ";
    }
    std::cout << std::endl;
  }
}

// ~~ Graphene::GraphInfo