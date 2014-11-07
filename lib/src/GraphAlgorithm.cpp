#include "GraphAlgorithm.h"

#include <algorithm>
#include <iostream>

using std::size_t;

namespace Graphene {

void Floyd_Warshall(const BaseGraph& graph, vector2d& distances_vec, vector2d& predecessors)
{
  size_t node_count = graph.GetNodes().size();
  auto all_edges = graph.GetEdges();
  ResizeVector2d(distances_vec, node_count, node_count);
  ResizeVector2d(predecessors, node_count, node_count);

  int** dist = new int*[node_count];
  for (int i = 0; i < node_count; ++i) {
    dist[i] = new int[node_count];
  }

  int** prec = new int*[node_count];
  for (int i = 0; i < node_count; ++i) {
    prec[i] = new int[node_count];
  }

  for (unsigned n1 = 0; n1 < node_count; ++n1) {
    for (unsigned n2 = 0; n2 < node_count; ++n2) {
      if (n1 != n2) 
        dist[n1][n2] = BaseGraph::INFINITE;
      else
        dist[n1][n2] = 0;
      prec[n1][n2] = BaseGraph::NODE_DONT_EXSISTS;
    }
  }
  for (auto edge : all_edges) {
    auto n1 = edge.base_node;
    auto n2 = edge.target_node;
    dist[n1][n2] = edge.weight;
    prec[n1][n2] = n1;
  }

  for (unsigned nu = 0; nu < node_count; ++nu) {
    for (unsigned n1 = 0; n1 < node_count; ++n1) {
      auto parital_dist = dist[n1][nu];
      if (parital_dist == BaseGraph::INFINITE || parital_dist == 0) continue;
      for (unsigned n2 = 0; n2 < node_count; ++n2) {
        if (dist[n1][n2] > parital_dist + dist[nu][n2]) {
          dist[n1][n2] = parital_dist + dist[nu][n2];
          prec[n1][n2] = prec[nu][n2];
        }
      }
    }
  }

  for (unsigned i = 0; i < node_count; ++i) {
    distances_vec[i].assign(dist[i], dist[i] + node_count);
    predecessors[i].assign(prec[i], prec[i] + node_count);
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
