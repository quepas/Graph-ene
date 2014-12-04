#include <iostream>

#include "GraphAlgorithm.h"
#include "GraphLoader.h"
#include "GraphInfo.h"
#include "AdjacencyMatrixGraph.h"
#include "AdjacencyListGraph.h"
#include "TimeWatch.h"

void DisplayStats(double time, int distance);
void DisplayMaxFlowStats(double time, int max_flow);

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

  std::cout << "\n### Ford-Fulkerson ###" << std::endl;
  watch.Reset();
  int max_flow = Graphene::Ford_Fulkerson(matrix_graph, FROM, TO);
  double ff_matrix_time = watch.Stop();
  DisplayMaxFlowStats(ff_matrix_time, max_flow);

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

  std::cout << "\n### Ford-Fulkerson ###" << std::endl;
  watch.Reset();
  max_flow = Graphene::Ford_Fulkerson(list_graph, FROM, TO);
  double ff_list_time = watch.Stop();
  DisplayMaxFlowStats(ff_list_time, max_flow);

  std::cout << "\nStats:\n\tFloyd-Warshall R: " << floyd_warshall_list_time / floyd_warshall_matrix_time << std::endl;
  std::cout << "\tBellman-Ford R: " << bellman_ford_list_time / bellman_ford_matrix_time << std::endl;
  std::cout << "\tFord-Fulkerson R: " << ff_list_time / ff_matrix_time << std::endl;

  getchar();
}

void DisplayStats(double time, int distance) {
  std::cout << "\tElapsed seconds: " << time << "s" << std::endl;
  std::cout << "\tDistance: " << distance << std::endl;
}

void DisplayMaxFlowStats(double time, int max_flow) {
  std::cout << "\tElapsed seconds: " << time << "s" << std::endl;
  std::cout << "\tMax flow: " << max_flow << std::endl;
}