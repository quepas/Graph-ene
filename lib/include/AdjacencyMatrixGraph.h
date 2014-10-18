#pragma once

#include "BaseGraph.h"

namespace Graphene {

class AdjacencyMatrixGraph : public BaseGraph
{
public:
  AdjacencyMatrixGraph() : capacity_(10), edge_count_(0) { ResizeMatrix(capacity_); };
  //AdjacencyMatrixGraph(std::size_t capacity) : capacity_(capacity), edge_count_(0) {};

  bool AddNode(unsigned node) override;
  bool RemoveNode(unsigned node) override;
  bool AddEdge(unsigned base_node, unsigned target_node, int value) override;
  bool RemoveEdge(unsigned base_node, unsigned target_node) override;
  std::vector<unsigned> GetNeighbours(unsigned node) override;
  std::vector<Edge> GetIncidentEdges(unsigned node) override;

  std::size_t GetEdgeCount() const override { return edge_count_; }
  std::size_t GetNodeCount() const override;
  std::size_t GetCapacity() const { return capacity_; }
  const std::vector<std::vector<unsigned>>& matrix() const { return matrix_; }

  bool IsCorrectNode(unsigned node) { return node > 0 && node <= capacity_; }
  bool IsNodeExsist(unsigned node);
  bool IsEdgeExsist(unsigned base_node, unsigned target_node);

private:
  std::size_t edge_count_;
  std::size_t capacity_;

  std::vector<std::vector<unsigned>> matrix_;

  void ResizeMatrix(std::size_t capacity);
  unsigned NodeToIndex(unsigned node) { return node - 1; }
  unsigned IndexToNode(unsigned index) { return index + 1; }

};

}
// ~~ Graphene::AdjacencyMatrixGraph