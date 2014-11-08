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
  DisplayStats(watch.Stop(), distances[FROM][TO]);
  Graphene::PrintPath(predecessors, FROM, TO);

  std::cout << "\n### Bellman-Ford ###" << std::endl;
  std::vector<int> weight, pred;
  watch.Reset();
  Graphene::Bellman_Ford(matrix_graph, weight, pred, FROM);
  DisplayStats(watch.Stop(), weight[TO]);
  Graphene::PrintPath(pred, FROM, TO);

  std::cout << "\n--------------- AdjacencyListGraph ---------------" << std::endl;
  Graphene::AdjacencyListGraph list_graph;
  Graphene::LoadGraph("data/big_graph.txt", list_graph);

  std::cout << "\n### Floyd-Warshall ###" << std::endl;
  watch.Reset();
  Graphene::Floyd_Warshall(list_graph, distances, predecessors);
  DisplayStats(watch.Stop(), distances[FROM][TO]);
  Graphene::PrintPath(predecessors, FROM, TO);

  std::cout << "\n### Bellman-Ford ###" << std::endl;
  watch.Reset();
  Graphene::Bellman_Ford(list_graph, weight, pred, FROM);
  DisplayStats(watch.Stop(), weight[TO]);
  Graphene::PrintPath(pred, FROM, TO);
}

void DisplayStats(double time, int distance) {
  std::cout << "\tElapsed seconds: " << time << "s" << std::endl;
  std::cout << "\tDistance: " << distance << std::endl;
}