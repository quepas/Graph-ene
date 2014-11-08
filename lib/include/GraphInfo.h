#pragma once

#include "GraphAlgorithm.h"
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

void PrintPath(const vector2d& prec, unsigned from, unsigned to) 
{
  std::string path = std::to_string(to);
  while (from != to) {
    path = std::to_string(prec[from][to]) + " " + path;
    to = prec[from][to];
  }
  std::cout << "\tPath: [" << path << "]" << std::endl;
}

void PrintPath(const std::vector<int>& prec, unsigned from, unsigned to)
{
  std::string path = std::to_string(to);
  while (from != to) {
    path = std::to_string(prec[to]) + " " + path;
    to = prec[to];
  }
  std::cout << "\tPath: [" << path << "]" << std::endl;
}

}
// ~~ Graphene::GraphInfo