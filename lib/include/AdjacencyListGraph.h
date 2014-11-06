#pragma once

#include "BaseGraph.h"

#include <list>

namespace Graphene {

struct EndNode {
  unsigned id;
  unsigned weight;
};

class AdjacencyListGraph : public BaseGraph
{
public:
  AdjacencyListGraph() {}

  bool AddNode(unsigned node) override;
  bool RemoveNode(unsigned node) override;
  bool AddEdge(unsigned base_node, unsigned target_node, int weight) override;
  bool RemoveEdge(unsigned base_node, unsigned target_node) override;

  std::vector<unsigned> GetAdjacentNodes(unsigned node) const override;
  std::vector<Edge> GetIncidentEdges(unsigned node) const override;
  int GetEdgeValue(unsigned base_node, unsigned target_node) const override;
  std::size_t GetEdgeCount() const override;
  std::size_t GetNodeCount() const override;

  bool IsNodeExsist(unsigned node) const override;
  bool IsEdgeExsist(unsigned base_node, unsigned target_node) const override;

private:
  std::vector<std::list<EndNode>> list_;
};

}
// ~~ Graphene::AdjacencyListGraph
