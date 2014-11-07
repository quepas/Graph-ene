#include "GraphAlgorithm.h"

#include <iostream>

using std::size_t;

namespace Graphene {

void Floyd_Warshall(const BaseGraph& graph, vector2d& d, vector2d& predecessors)
{
  auto all_nodes = graph.GetNodes();
  size_t node_count = all_nodes.size();
  auto all_edges = graph.GetEdges();

  ResizeVector2d(d, node_count, node_count);
  ResizeVector2d(predecessors, node_count, node_count);

  for (auto n1 : all_nodes) {
    for (auto n2 : all_nodes) {
      d[n1][n2] = BaseGraph::INFINITE;
      predecessors[n1][n2] = BaseGraph::NODE_DONT_EXSISTS;
    }
    d[n1][n1] = 0;
  }
  for (auto edge : all_edges) {
    auto n1 = edge.base_node;
    auto n2 = edge.target_node;
    d[n1][n2] = edge.weight;
    predecessors[n1][n2] = n1;
  }

  for (auto nu : all_nodes) {
    for (auto n1 : all_nodes) {
      for (auto n2 : all_nodes) {
        if (d[n1][n2] > d[n1][nu] + d[nu][n2]) {
          d[n1][n2] = d[n1][nu] + d[nu][n2];
          predecessors[n1][n2] = predecessors[nu][n2];
        }
      }
    }
    std::cout << "#";
  }
}

void ResizeVector2d(vector2d& vector, unsigned first_dimension, unsigned second_dimension)
{
  vector.resize(first_dimension + 1);
  for (auto& row : vector) {
    row.resize(second_dimension + 1);
  }
}

void FillVector2d(vector2d& vector, int value)
{
  for (unsigned row = 0; row < vector.size(); ++row) {
    for (unsigned col = 0; col < vector.size(); ++col) {
      vector[row][col] = value;
    }
  }
}

}
// ~~ Graphene::GraphAlgorithm
