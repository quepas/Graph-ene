#pragma once

#include "BaseGraph.h"

namespace Graphene {

template <typename T>
class AdjacencyMatrixGraph : public BaseGraph<T>
{
public:
  AdjacencyMatrixGraph() : capacity_(10), edge_count_(0), node_count_(0) { ResizeMatrix(capacity_); };
  //AdjacencyMatrixGraph(std::size_t capacity) : capacity_(capacity), edge_count_(0), node_count_(0) {};

  bool AddNode(unsigned node) override;
  bool RemoveNode(unsigned node) override;
  bool AddEdge(unsigned base_node, unsigned target_node, int value) override;
  bool RemoveEdge(unsigned base_node, unsigned target_node) override;
  std::vector<unsigned> GetNeighbours(unsigned node) override;
  std::vector<Edge<T>> GetIncidentEdges(unsigned node) override;

  std::size_t GetEdgeCount() const override { return edge_count_; };
  std::size_t GetNodeCount() const override { return node_count_; };
  std::size_t GetCapacity() const { return capacity_ };
  const std::vector<std::vector<unsigned>>& matrix() const { return matrix_; }

  bool IsCorrectNode(unsigned node) { return node > 0 && node <= capacity_; }
  bool IsNodeExsist(unsigned node);
  bool IsEdgeExsist(unsigned base_node, unsigned target_node);

private:
  std::size_t edge_count_;
  std::size_t node_count_;
  std::size_t capacity_;

  std::vector<std::vector<unsigned>> matrix_;

  void ResizeMatrix(std::size_t capacity);
  unsigned NodeToIndex(unsigned node) { return node - 1; }
  unsigned IndexToNode(unsigned index) { return index + 1; }
};

template <typename T>
bool AdjacencyMatrixGraph<T>::IsNodeExsist(unsigned node)
{
  if (IsCorrectNode(node)) {
    auto idx = NodeToIndex(node);
    return matrix_[idx][idx] == 1;
  }
  return false;
}

template <typename T>
bool AdjacencyMatrixGraph<T>::IsEdgeExsist(unsigned base_node, unsigned target_node)
{
  if (IsNodeExsist(base_node) && IsNodeExsist(target_node)) {
    return matrix_[NodeToIndex(base_node)][NodeToIndex(target_node)] != 0;
  }
  return false;
}

template <typename T>
void AdjacencyMatrixGraph<T>::ResizeMatrix(std::size_t capacity)
{
  capacity_ = capacity;
  matrix_.resize(capacity_);
  for (unsigned i = 0; i < capacity_; ++i) {
    matrix_[i].resize(capacity_);
    for (unsigned j = 0; j < capacity_; ++j) {
      matrix_[i][j] = 0;
    }
  }
}

template <typename T>
std::vector<Edge<T>> AdjacencyMatrixGraph<T>::GetIncidentEdges(unsigned node)
{
  return std::vector<Edge<T>>();
}

template <typename T>
std::vector<unsigned> AdjacencyMatrixGraph<T>::GetNeighbours(unsigned node)
{
  std::vector<unsigned> result;
  if (IsNodeExsist(node)) {
    auto idx = NodeToIndex(node);
    auto& row = matrix_[idx];
    for (unsigned i = 0; i < row.size(); ++i) {
      if (i != idx && row[i] != 0) {
        result.push_back(IndexToNode(i));
      }
    }
  }
  return result;
}

template <typename T>
bool AdjacencyMatrixGraph<T>::RemoveEdge(unsigned base_node, unsigned target_node)
{
  if (IsEdgeExsist(base_node, target_node)) {
    matrix_[NodeToIndex(base_node)][NodeToIndex(target_node)] = 0;
    --edge_count_;
  }
  return false;
}

template <typename T>
bool AdjacencyMatrixGraph<T>::AddEdge(unsigned base_node, unsigned target_node, int value)
{
  if (IsNodeExsist(base_node) && IsNodeExsist(target_node)) {
    matrix_[NodeToIndex(base_node)][NodeToIndex(target_node)] = value;
    ++edge_count_;
  }
  return false;
}

template <typename T>
bool AdjacencyMatrixGraph<T>::RemoveNode(unsigned node)
{
  if (IsNodeExsist(node)) {
    auto idx = NodeToIndex(node);
    // remove 'node id' row
    auto& row = matrix_[idx];
    for (auto& element : row) {
      element = 0;
    }
    // remove 'node id' col
    for (auto& row : matrix_) {
      row[idx] = 0;
    }
    --node_count_;
    return true;
  }
  return false;
}

template <typename T>
bool AdjacencyMatrixGraph<T>::AddNode(unsigned node)
{
  if (IsCorrectNode(node)) {
    auto idx = NodeToIndex(node);
    matrix_[idx][idx] = 1;
    ++node_count_;
    return true;
  }
  return false;
}

}
// ~~ Graphene::AdjacencyMatrixGraph