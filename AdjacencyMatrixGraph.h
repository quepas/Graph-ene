#pragma once

#include "BaseGraph.h"

namespace Graphene {

template <typename T>
class AdjacencyMatrixGraph : public BaseGraph<T>
{
public:
  AdjacencyMatrixGraph() : capacity_(10), edge_count_(0), node_count_(0) { InitMatrix(); };
  AdjacencyMatrixGraph(std::size_t capacity) : capacity_(capacity), edge_count_(0), node_count_(0) {};

  bool AddNode(unsigned node) override;
  bool RemoveNode(unsigned node) override;
  bool AddEdge(unsigned base_node, unsigned target_node) override;
  bool RemoveEdge(unsigned base_node, unsigned target_node) override;
  std::vector<unsigned> GetNeighbours(unsigned node) override;
  std::vector<Edge<T>> GetIncidentEdges(unsigned node) override;

  std::size_t GetEdgeCount() const override { return edge_count_; };
  std::size_t GetNodeCount() const override { return node_count_; };
  std::size_t GetCapacity() const { return capacity_ };
  const std::vector<std::vector<unsigned>>& matrix() const { return matrix_; }

  bool InAdjacent(unsigned base_node, unsigned target_node) const override;

private:
  std::size_t edge_count_;
  std::size_t node_count_;
  std::size_t capacity_;

  std::vector<std::vector<unsigned>> matrix_;

  void InitMatrix();
};

template <typename T>
bool Graphene::AdjacencyMatrixGraph<T>::InAdjacent(unsigned base_node, unsigned target_node) const
{
  return false;
}

template <typename T>
void Graphene::AdjacencyMatrixGraph<T>::InitMatrix()
{
  matrix_.resize(capacity_);
  for (unsigned i = 0; i < capacity_; ++i) {
    matrix_[i].resize(capacity_);
    for (unsigned j = 0; j < capacity_; ++j) {
      matrix_[i][j] = 0;
    }
  }
}

template <typename T>
std::vector<Edge<T>> Graphene::AdjacencyMatrixGraph<T>::GetIncidentEdges(unsigned node)
{
  return std::vector<Edge<T>>();
}

template <typename T>
std::vector<unsigned> Graphene::AdjacencyMatrixGraph<T>::GetNeighbours(unsigned node)
{
  return std::vector<unsigned>();
}

template <typename T>
bool Graphene::AdjacencyMatrixGraph<T>::RemoveEdge(unsigned base_node, unsigned target_node)
{
  return false;
}

template <typename T>
bool Graphene::AdjacencyMatrixGraph<T>::AddEdge(unsigned base_node, unsigned target_node)
{
  return false;
}

template <typename T>
bool Graphene::AdjacencyMatrixGraph<T>::RemoveNode(unsigned node)
{
  return false;
}

template <typename T>
bool Graphene::AdjacencyMatrixGraph<T>::AddNode(unsigned node)
{
  return false;
}

}
// ~~ Graphene::AdjacencyMatrixGraph