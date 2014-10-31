#pragma once

#include <vector>

namespace Graphene {

struct Edge {
  unsigned base_node;
  unsigned target_node;
  int weight;
};

class BaseGraph
{
public:
  virtual ~BaseGraph() {}

  virtual bool AddNode(unsigned node) = 0;
  virtual bool RemoveNode(unsigned node) = 0;
  virtual bool AddEdge(unsigned base_node, unsigned target_node, int weight) = 0;
  virtual bool RemoveEdge(unsigned base_node, unsigned target_node) = 0;
  
  virtual std::vector<unsigned> GetAdjacentNodes(unsigned node) const = 0;
  virtual std::vector<Edge> GetIncidentEdges(unsigned node) const = 0;
  virtual std::size_t GetEdgeCount() const = 0;
  virtual std::size_t GetNodeCount() const = 0;

};

}
// ~~ Graphene::BaseGraph
