#include "GraphAlgorithm.h"

#include <iostream>

using std::size_t;

namespace Graphene {

void Floyd_Warshall(const BaseGraph& graph, vector2d& distances_vec, vector2d& predecessors)
{
  auto all_nodes = graph.GetNodes();
  size_t node_count = all_nodes.size();
  auto all_edges = graph.GetEdges();
  ResizeVector2d(distances_vec, node_count, node_count);
  ResizeVector2d(predecessors, node_count, node_count);

  int** dist = new int*[node_count];
  for (int i = 0; i < node_count; ++i) {
    dist[i] = new int[node_count];
  }

  for (auto n1 : all_nodes) {
    for (auto n2 : all_nodes) {
      if (n1 != n2) 
        dist[n1][n2] = BaseGraph::INFINITE;
      else
        dist[n1][n2] = 0;
      predecessors[n1][n2] = BaseGraph::NODE_DONT_EXSISTS;
    }
  }
  for (auto edge : all_edges) {
    auto n1 = edge.base_node;
    auto n2 = edge.target_node;
    dist[n1][n2] = edge.weight;
    predecessors[n1][n2] = n1;
  }

  for (unsigned nu = 0; nu < node_count; ++nu) {
    for (unsigned n1 = 0; n1 < node_count; ++n1) {
      auto partial_dist = dist[n1][nu];
      if (partial_dist == BaseGraph::INFINITE || partial_dist == 0) continue;
      for (unsigned n2 = 0; n2 < node_count; ++n2) {
        if (dist[n1][n2] > partial_dist + dist[nu][n2]) {
          dist[n1][n2] = partial_dist + dist[nu][n2];
          predecessors[n1][n2] = predecessors[nu][n2];
        }
      }
    }
  }

  for (unsigned i = 0; i < node_count; ++i) {
    for (unsigned j = 0; j < node_count; ++j) {
      distances_vec[i][j] = dist[i][j];
    }
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
