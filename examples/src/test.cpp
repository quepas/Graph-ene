#include <iostream>

#include "GraphAlgorithm.h"
#include "GraphLoader.h"
#include "GraphInfo.h"
#include "AdjacencyMatrixGraph.h"
#include "AdjacencyListGraph.h"
#include "TimeWatch.h"

void DisplayStats(double time, int distance);

int main() {
  const unsigned FROM = 109;
  const unsigned TO = 609;

  std::cout << "\n--------------- AdjacencyMatrixGraph ---------------" << std::endl;
  Graphene::AdjacencyMatrixGraph matrix_graph;
  Graphene::LoadGraph("data/big_graph.txt", matrix_graph);

  std::cout << "\n### Floyd-Warshall ###" << std::endl;
  Graphene::vector2d distances;
  Graphene::vector2d predecessors;
  Graphene::TimeWatch watch;
  Graphene::Floyd_Warshall(matrix_graph, distances, predecessors);
  double floyd_warshall_matrix_time = watch.Stop();
  DisplayStats(floyd_warshall_matrix_time, distances[FROM][TO]);
  Graphene::PrintPath(predecessors, FROM, TO);

  std::cout << "\n### Bellman-Ford ###" << std::endl;
  std::vector<int> weight, pred;
  watch.Reset();
  Graphene::Bellman_Ford(matrix_graph, weight, pred, FROM);
  double bellman_ford_matrix_time = watch.Stop();
  DisplayStats(bellman_ford_matrix_time, weight[TO]);
  Graphene::PrintPath(pred, FROM, TO);

  std::cout << "\n--------------- AdjacencyListGraph ---------------" << std::endl;
  Graphene::AdjacencyListGraph list_graph;
  Graphene::LoadGraph("data/big_graph.txt", list_graph);

  std::cout << "\n### Floyd-Warshall ###" << std::endl;
  watch.Reset();
  Graphene::Floyd_Warshall(list_graph, distances, predecessors);
  double floyd_warshall_list_time = watch.Stop();
  DisplayStats(floyd_warshall_list_time, distances[FROM][TO]);
  Graphene::PrintPath(predecessors, FROM, TO);

  std::cout << "\n### Bellman-Ford ###" << std::endl;
  watch.Reset();
  Graphene::Bellman_Ford(list_graph, weight, pred, FROM);
  double bellman_ford_list_time = watch.Stop();
  DisplayStats(bellman_ford_list_time, weight[TO]);
  Graphene::PrintPath(pred, FROM, TO);

  std::cout << "\nStats:\n\tFloyd-Warshall R: " << floyd_warshall_list_time / floyd_warshall_matrix_time << std::endl;
  std::cout << "\tBellman-Ford R: " << bellman_ford_list_time / bellman_ford_matrix_time << std::endl;
}

void DisplayStats(double time, int distance) {
  std::cout << "\tElapsed seconds: " << time << "s" << std::endl;
  std::cout << "\tDistance: " << distance << std::endl;
}