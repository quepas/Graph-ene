#pragma once

#include "BaseGraph.h"

#include <list>

namespace Graphene {

struct EndNode {
  unsigned id;
  int weight;
};

class AdjacencyListGraph : public BaseGraph
{
public:
  AdjacencyListGraph() 
    : capacity_(INITIAL_CAPACITY) 
  {
    SetupList(capacity_);
  }

  AdjacencyListGraph(std::size_t capacity) 
    : capacity_(capacity) 
  {
    SetupList(capacity_);
  }

  bool AddNode(unsigned node) override;
  bool RemoveNode(unsigned node) override;
  bool AddEdge(unsigned base_node, unsigned target_node, int weight) override;
  bool RemoveEdge(unsigned base_node, unsigned target_node) override;

  std::vector<unsigned> GetNodes() const override;
  std::vector<Edge> GetEdges() const override;
  std::vector<unsigned> GetIncidentNodes(unsigned node) const override;
  std::vector<unsigned> GetAdjacentNodes(unsigned node) const override;
  std::vector<Edge> GetIncidentEdges(unsigned node) const override;
  std::vector<Edge> GetAdjacentEdges(unsigned node) const override;
  int GetEdgeValue(unsigned base_node, unsigned target_node) const override;
  void SetEdgeValue(unsigned base_node, unsigned target_node, int value) override;
  std::size_t GetEdgeCount() const override;
  std::size_t GetNodeCount() const override;
  const std::vector<std::list<EndNode>>& list() const { return list_; }

  bool IsCorrectNodeIdx(unsigned node) const { return node < capacity_; }
  bool IsNodeExsist(unsigned node) const override;
  bool IsEdgeExsist(unsigned base_node, unsigned target_node) const override;
  bool AreNodesAdjacent(unsigned base_node, unsigned target_node) const override;
  bool AreNodesIncident(unsigned base_node, unsigned target_node) const override;

  AdjacencyListGraph* Copy() const { return new AdjacencyListGraph(*this); }
  AdjacencyListGraph* Create() const { return new AdjacencyListGraph(); }

  void Resize(std::size_t node_capacity) {
    SetupList(node_capacity);
  }

private:
  std::size_t capacity_;

  std::vector<std::list<EndNode>> list_;
  std::vector<bool> nodes_ex_;

  void SetupList(std::size_t capacity);
};

}
// ~~ Graphene::AdjacencyListGraph
