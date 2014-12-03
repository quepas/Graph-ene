#include "GraphAlgorithm.h"

#include <algorithm>
#include <queue>
#include <set>
#include <iostream>

using std::cout;
using std::endl;
using std::size_t;
using std::set;
using std::queue;

namespace Graphene {

void Floyd_Warshall(const BaseGraph& graph, vector2d& distances_vec, vector2d& predecessors)
{
  size_t node_count = graph.GetNodes().size();
  auto all_edges = graph.GetEdges();
  ResizeVector2d(distances_vec, node_count, node_count);
  ResizeVector2d(predecessors, node_count, node_count);

  int** dist = new int*[node_count];
  int** prec = new int*[node_count];
  for (int i = 0; i < node_count; ++i) {
    dist[i] = new int[node_count];
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

void Bellman_Ford(const BaseGraph& graph, std::vector<int>& distances_vec, std::vector<int>& predecessors, unsigned source) {
  auto all_nodes = graph.GetNodes();
  size_t node_count = all_nodes.size();
  auto all_edges = graph.GetEdges();

  distances_vec.resize(node_count);
  predecessors.resize(node_count);

  int* dist = new int[node_count];
  int* pred = new int[node_count];
  // Step 1: initialize graph
  for (auto node : all_nodes) {
    if (node == source) dist[node] = 0;
    else dist[node] = BaseGraph::INFINITE;
    pred[node] = -1;
  }
  // Step 2: relax edges repeatedly
  for (unsigned i = 0; i < node_count; ++i) {
    for (auto edge : all_edges) {
      if (dist[edge.base_node] + edge.weight < dist[edge.target_node]) {
        dist[edge.target_node] = dist[edge.base_node] + edge.weight;
        pred[edge.target_node] = edge.base_node;
      }
    }
  }
  distances_vec.assign(dist, dist + node_count);
  predecessors.assign(pred, pred + node_count);
  // step 3: no implementation for checking negative-weight cycles
}

void Ford_Fulkerson(const BaseGraph& graph, unsigned source, unsigned target, unsigned**& capacity, unsigned**& floating)
{
}

void ResizeVector2d(vector2d& vector, unsigned first_dimension, unsigned second_dimension)
{
  vector.resize(first_dimension + 1);
  for (auto& row : vector) {
    row.resize(second_dimension + 1);
  }
}

void Breadth_First_Search(const BaseGraph& graph, unsigned start, int*& parents)
{
  auto num_node = graph.GetNodeCount();
  parents = new int[num_node]();

  queue<unsigned> to_visit;
  set<unsigned> visited;

  visited.insert(start);
  to_visit.push(start);

  unsigned current;
  while (!to_visit.empty()) {
    current = to_visit.front();
    to_visit.pop();

    for (Edge edge : graph.GetAdjacentEdges(current)) {
      unsigned child = edge.target_node;
      if (visited.find(child) == visited.end()) {
        visited.insert(child);
        to_visit.push(child);
        parents[child] = current;
      }
    }
  }
}

void FindBFSPath(int*& parents, int start, int end, std::vector<unsigned>& path) {
  if ((start == end) || (end == -1)) {
    path.push_back(start);
    std::reverse(path.begin(), path.end());
  }
  else {
    path.push_back(end);
    FindBFSPath(parents, start, parents[end], path);
  }
}

}
// ~~ Graphene::GraphAlgorithm
