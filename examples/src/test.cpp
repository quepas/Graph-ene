#include <iostream>

#include "GraphAlgorithm.h"
#include "GraphLoader.h"
#include "GraphInfo.h"
#include "AdjacencyMatrixGraph.h"
#include "AdjacencyListGraph.h"
#include "TimeWatch.h"

int main() {
  Graphene::AdjacencyMatrixGraph graph;
  Graphene::LoadGraph("data/big_graph.txt", graph);

  Graphene::vector2d d;
  Graphene::vector2d prec;
  Graphene::TimeWatch watch;
  Graphene::Floyd_Warshall(graph, d, prec);

  std::cout << "\n--------------- AdjacencyMatrixGraph ---------------" << std::endl;
  std::cout << "Elapsed seconds: " << watch.Stop() << "s" << std::endl;
  std::cout << "Distance: " << d[109][609] << std::endl;
  Graphene::PrintPath(prec, 109, 609);

  Graphene::AdjacencyListGraph graph2;
  Graphene::LoadGraph("data/big_graph.txt", graph2);

  Graphene::vector2d d2;
  Graphene::vector2d prec2;
  Graphene::TimeWatch watch2;
  Graphene::Floyd_Warshall(graph2, d2, prec2);

  std::cout << "\n--------------- AdjacencyListGraph ---------------" << std::endl;
  std::cout << "Elapsed seconds: " << watch2.Stop() << "s" << std::endl;
  std::cout << "Distance: " << d2[109][609] << std::endl;
  Graphene::PrintPath(prec2, 109, 609);

}