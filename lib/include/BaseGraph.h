#pragma once

#include <climits>
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

  virtual std::vector<unsigned> GetNodes() const = 0;
  virtual std::vector<Edge> GetEdges() const = 0;
  virtual std::vector<unsigned> GetAdjacentNodes(unsigned node) const = 0;
  virtual std::vector<Edge> GetIncidentEdges(unsigned node) const = 0;
  virtual std::vector<Edge> GetAdjacentEdges(unsigned node) const = 0;
  virtual int GetEdgeValue(unsigned base_node, unsigned target_node) const = 0;
  virtual std::size_t GetEdgeCount() const = 0;
  virtual std::size_t GetNodeCount() const = 0;

  virtual bool IsNodeExsist(unsigned node) const = 0;
  virtual bool IsEdgeExsist(unsigned base_node, unsigned target_node) const = 0;
  virtual bool AreNodesAdjacent(unsigned base_node, unsigned target_node) const = 0;
  virtual bool AreNodesIncident(unsigned base_node, unsigned target_node) const = 0;

  static const int INFINITE = INT_MAX;
  static const int NODE_EXSISTS = 0;
  static const int NODE_DONT_EXSISTS = 0;
  static const int INITIAL_CAPACITY = 10;

};

}
// ~~ Graphene::BaseGraph
