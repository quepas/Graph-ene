#pragma once

#include <vector>

namespace Graphene {

struct Edge {
  unsigned base_node;
  unsigned target_node;
  int value;
};

class BaseGraph
{
public:
  virtual ~BaseGraph() {}

  virtual bool AddNode(unsigned node) = 0;
  virtual bool RemoveNode(unsigned node) = 0;
  virtual bool AddEdge(unsigned base_node, unsigned target_node, int value) = 0;
  virtual bool RemoveEdge(unsigned base_node, unsigned target_node) = 0;
  virtual std::vector<unsigned> GetNeighbours(unsigned node) = 0;
  virtual std::vector<Edge> GetIncidentEdges(unsigned node) = 0;

  virtual std::size_t GetEdgeCount() const = 0;
  virtual std::size_t GetNodeCount() const = 0;

};

}
// ~~ Graphene::BaseGraph