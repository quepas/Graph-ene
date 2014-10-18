#pragma once

#include "AdjacencyMatrixGraph.h"

#include <iostream>

namespace Graphene {

void PrintAdjacencyMatrix(const AdjacencyMatrixGraph& graph);

void PrintNodes(const std::vector<unsigned>& nodes);

void PrintAdjacencyMatrix(const AdjacencyMatrixGraph& graph)
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