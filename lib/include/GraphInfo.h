#pragma once

#include "AdjacencyMatrixGraph.h"

#include <iostream>
#include <string>

namespace Graphene {

void PrintAdjacencyMatrix(const AdjacencyMatrixGraph& graph);

void PrintNodes(const std::vector<unsigned>& nodes);

void PrintAdjacencyMatrix(const AdjacencyMatrixGraph& graph)
{
  unsigned row_counter = 0;
  for (auto& row : graph.matrix()) {
    std::cout << row_counter++ << ": ";
    for (auto& col : row) {
      if (col == AdjacencyMatrixGraph::INFINITE)
        std::cout << "Inf" << " ";
      else
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