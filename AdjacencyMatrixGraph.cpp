#include "AdjacencyMatrixGraph.h"

using std::size_t;
using std::vector;

namespace Graphene {

bool AdjacencyMatrixGraph::IsNodeExsist(unsigned node)
{
  if (IsCorrectNode(node)) {
    auto idx = NodeToIndex(node);
    return matrix_[idx][idx] == 1;
  }
  return false;
}

bool AdjacencyMatrixGraph::IsEdgeExsist(unsigned base_node, unsigned target_node)
{
  if (IsNodeExsist(base_node) && IsNodeExsist(target_node)) {
    return matrix_[NodeToIndex(base_node)][NodeToIndex(target_node)] != 0;
  }
  return false;
}

void AdjacencyMatrixGraph::ResizeMatrix(size_t capacity)
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

vector<Edge> AdjacencyMatrixGraph::GetIncidentEdges(unsigned node)
{
  return vector<Edge>();
}

vector<unsigned> AdjacencyMatrixGraph::GetNeighbours(unsigned node)
{
  vector<unsigned> result;
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

bool AdjacencyMatrixGraph::RemoveEdge(unsigned base_node, unsigned target_node)
{
  if (IsEdgeExsist(base_node, target_node)) {
    matrix_[NodeToIndex(base_node)][NodeToIndex(target_node)] = 0;
    --edge_count_;
  }
  return false;
}

bool AdjacencyMatrixGraph::AddEdge(unsigned base_node, unsigned target_node, int value)
{
  if (IsNodeExsist(base_node) && IsNodeExsist(target_node)) {
    matrix_[NodeToIndex(base_node)][NodeToIndex(target_node)] = value;
    ++edge_count_;
  }
  return false;
}

bool AdjacencyMatrixGraph::RemoveNode(unsigned node)
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

bool AdjacencyMatrixGraph::AddNode(unsigned node)
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
