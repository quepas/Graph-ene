#pragma once

#include "BaseGraph.h"

namespace Graphene {

class AdjacencyMatrixGraph : public BaseGraph
{
public:
  AdjacencyMatrixGraph()
    : capacity_(INITIAL_CAPACITY)
  {
    SetupMatrix(capacity_);
  }
  AdjacencyMatrixGraph(std::size_t capacity)
    : capacity_(capacity)
  {
    SetupMatrix(capacity_);
  }

  ~AdjacencyMatrixGraph() {
    for (unsigned idx = 0; idx < capacity_; ++idx) {
      delete [] matrix_[idx];
    }
    delete [] matrix_;
  }

  bool AddNode(unsigned node) override;
  bool RemoveNode(unsigned node) override;
  bool AddEdge(unsigned base_node, unsigned target_node, int weight) override;
  bool RemoveEdge(unsigned base_node, unsigned target_node) override;

  std::vector<unsigned> GetIncidentNodes(unsigned node) const override;
  std::vector<unsigned> GetAdjacentNodes(unsigned node) const override;
  std::vector<Edge> GetIncidentEdges(unsigned node) const override;
  std::vector<Edge> GetAdjacentEdges(unsigned node) const override;
  int GetEdgeValue(unsigned base_node, unsigned target_node) const override;
  void SetEdgeValue(unsigned base_node, unsigned target_node, int value) override;

  std::vector<unsigned> GetNodes() const override;
  std::vector<Edge> GetEdges() const override;
  std::size_t GetEdgeCount() const override;
  std::size_t GetNodeCount() const override;
  std::size_t GetCapacity() const { return capacity_; }
  int** const matrix() const { return matrix_; }

  bool IsCorrectNodeIdx(unsigned node) const { return node < capacity_; }
  bool IsNodeExsist(unsigned node) const;
  bool IsEdgeExsist(unsigned base_node, unsigned target_node) const;
  bool AreNodesAdjacent(unsigned base_node, unsigned target_node) const override;
  bool AreNodesIncident(unsigned base_node, unsigned target_node) const override;

  AdjacencyMatrixGraph* Copy() const { return new AdjacencyMatrixGraph(*this); }
  AdjacencyMatrixGraph* Create() const { return new AdjacencyMatrixGraph(); }

  void Resize(std::size_t node_capacity) {
    SetupMatrix(node_capacity);
  }

private:
  std::size_t capacity_;
  int** matrix_;

  void SetupMatrix(std::size_t capacity);

};

}
// ~~ Graphene::AdjacencyMatrixGraph