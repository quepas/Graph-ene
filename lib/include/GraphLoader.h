#pragma once

#include "BaseGraph.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

namespace Graphene {

bool LoadGraph(std::string path, BaseGraph& graph) {
  std::ifstream file(path);

  if (!file.is_open()) {
    std::cout << "Wrong file path." << std::endl;
    return false;
  }

  std::vector<Edge> edges;
  std::string line;
  int counter = 0;
  int max_node_id = -1;
  while (std::getline(file, line)) {
    ++counter;
    std::stringstream istream;
    int a, b, c;
    char z;
    istream << line;
    if (line.empty()) continue;
    istream >> a >> z >>  b  >> z >> c;
    if (a > max_node_id)
      max_node_id = a;
    if (b > max_node_id)
      max_node_id = b;
    edges.push_back({ 
      static_cast<unsigned>(a), 
      static_cast<unsigned>(b), 
      static_cast<unsigned>(c) });
  }
  graph.Resize(max_node_id + 1);
  for (auto edge : edges) {
    graph.AddNode(edge.base_node);
    graph.AddNode(edge.target_node);
    graph.AddEdge(edge.base_node, edge.target_node, edge.weight);
  }

  std::cout << "edges@" << path << " " << counter << std::endl;
  std::cout << "nodes@" << path << " " << graph.GetNodeCount() << std::endl;
}

}
// ~~ graphene::GraphLoader
