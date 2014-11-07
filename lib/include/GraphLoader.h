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
    std::cout << "Wrong file path.";
    return false;
  }

  std::vector<Edge> edges;
  std::string line;
  int counter = 0;
  while (std::getline(file, line)) {
    std::stringstream istream;
    int a, b, c;
    char z;
    istream << line;
    istream >> a >> z >>  b  >> z >> c;
    graph.AddNode(a);
    graph.AddNode(b);
    graph.AddEdge(a, b, c);
  }
}

}
// ~~ graphene::GraphLoader
