#pragma once

#include "BaseGraph.h"

namespace Graphene {

template <typename T>
class AdjacencyListGraph : public BaseGraph<T>
{
public:
  struct Node {
    T value;
    std::vector<Node*> neighbours;
  };


};

}
// ~~ Graphene::AdjacencyListGraph
