#include "GraphAlgorithm.h"
#include "AdjacencyMatrixGraph.h"
#include <algorithm>
#include <queue>
#include <set>
#include <string>
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

  int **dist, **prec;
  Initialize2DArray(dist, node_count+1, 0);
  Initialize2DArray(prec, node_count+1, 0);

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
  Delete2DArray(dist, node_count + 1);
  Delete2DArray(prec, node_count + 1);
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
  delete [] dist;
  delete [] pred;
  // step 3: no implementation for checking negative-weight cycles
}

void PrintEdgePath(const std::vector<Edge>& edges) {
  std::cout << "[";
  for (auto edge : edges) {
    std::cout << edge.base_node << " ";
  }
  std::cout << "]\n";
}

int Ford_Fulkerson(const BaseGraph& graph, unsigned source, unsigned target, int**& capacity, int**& floating)
{
  auto num_node = graph.GetNodeCount();
  Initialize2DArray(capacity, num_node+1, 0);
  Initialize2DArray(floating, num_node+1, 0);

  for (unsigned i = 0; i < num_node; ++i) {
    for (unsigned j = 0; j < num_node; ++j) {
      capacity[i][j] = graph.GetEdgeValue(i, j);
    }
  }
  do {
    AdjacencyMatrixGraph cgraph;
    cgraph.Resize(num_node);
    for (auto edge : graph.GetEdges()) {
      int v1 = edge.base_node;
      int v2 = edge.target_node;
     
      auto flow = floating[v1][v2];
      auto cap = capacity[v1][v2];
      if (flow < cap) {
        cgraph.AddNode(v1);
        cgraph.AddNode(v2);
        cgraph.AddEdge(v1, v2, cap-flow);
      }
    }
    // Find path p
    std::vector<Edge> edges_path;
    FindFirstPathBFS(cgraph, source, target, edges_path);
    if (edges_path.empty()) {
      int sum = 0;
      for (auto edge : graph.GetAdjacentEdges(source))
        sum += floating[edge.base_node][edge.target_node];
      return sum;
    }
    // Find minumum
    Edge min = edges_path[0];
    for (unsigned i = 1; i < edges_path.size(); ++i) {
      if (edges_path[i].weight < min.weight) min = edges_path[i];
    }
    int flow = min.weight;
    for (auto edge : edges_path) {
      auto v1 = edge.base_node;
      auto v2 = edge.target_node;
      floating[v1][v2] += flow;
      floating[v2][v1] -= flow;
    }
  } while (true);
  return -1;
}

void ResizeVector2d(vector2d& vector, unsigned first_dimension, unsigned second_dimension)
{
  for (unsigned i = 0; i < vector.size(); ++i) {
    vector[i].clear();
  }
  vector.clear();
  vector.resize(first_dimension + 1);
  for (auto& row : vector) {
    row.resize(second_dimension + 1);
  }
}

void RetrivePathFromBFS(int*& parents, int start, int end, std::vector<unsigned>& path)
{
  int current = end;
  while (true) {
    if (current == -1) {
      path.clear();
      break;
    }
    path.push_back(current);
    if (current == start) {
      std::reverse(path.begin(), path.end());
      break;
    }
    current = parents[current];
  }
}

void FindFirstPathBFS(const BaseGraph& graph, unsigned start, unsigned target, std::vector<Edge>& path)
{
  auto num_node = graph.GetNodeCount();
  int* parents = new int[num_node]();
  for (unsigned i = 0; i < num_node; ++i) { parents[i] = -1; }

  queue<unsigned> to_visit;
  set<unsigned> visited;

  visited.insert(start);
  to_visit.push(start);

  unsigned current;
  bool running = true;
  while (!to_visit.empty() && running) {
    current = to_visit.front();
    to_visit.pop();

    for (Edge edge : graph.GetAdjacentEdges(current)) {
      unsigned child = edge.target_node;
      if (visited.find(child) == visited.end()) {
        visited.insert(child);
        to_visit.push(child);
        parents[child] = current;
        if (current == target) {
          running = false;
          break;
        }
      }
    }
  }
  std::vector<unsigned> pp;
  RetrivePathFromBFS(parents, start, target, pp);
  PathToEdgePath(graph, pp, path);
}

void PathToEdgePath(const BaseGraph& graph, const std::vector<unsigned>& path, std::vector<Edge>& out_path)
{
  if (path.size() > 1) {
    for (unsigned i = 0; i < path.size() - 1; ++i) {
      unsigned v1 = path[i], v2 = path[i + 1];
      out_path.push_back({ v1, v2, graph.GetEdgeValue(v1, v2) });
    }
  }
}

}
// ~~ Graphene::GraphAlgorithm
