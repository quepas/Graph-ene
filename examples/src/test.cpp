#include <iostream>

#include "GraphInfo.h"
#include "AdjacencyMatrixGraph.h"

int main() {
  Graphene::AdjacencyMatrixGraph graph;

  graph.AddNode(3);
  graph.AddNode(6);
  graph.AddEdge(3, 6, 22);
  std::cout << "\nEdge 3-6: " << graph.IsEdgeExsist(3, 6);
  std::cout << "\nEdge 6-3: " << graph.IsEdgeExsist(6, 3);
  graph.AddEdge(6, 3, 32);
  std::cout << "\nEdge 6-3: " << graph.IsEdgeExsist(6, 3);
  std::cout << "\nNode 3: " << graph.IsNodeExsist(3) << std::endl;
  graph.RemoveNode(3);
  std::cout << "\nNode 3: " << graph.IsNodeExsist(3) << std::endl;
  graph.AddNode(9);
  std::cout << "Neighbours: ";
  Graphene::PrintNodes(graph.GetNeighbours(3));

  Graphene::PrintAdjacencyMatrix(graph);
}