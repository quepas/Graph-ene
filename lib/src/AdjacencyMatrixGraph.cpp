#include "AdjacencyMatrixGraph.h"

using std::size_t;
using std::vector;

namespace Graphene {

bool AdjacencyMatrixGraph::AddNode(unsigned node)
{
  if (IsCorrectNodeIdx(node)) {
    matrix_[node][node] = NODE_EXSISTS;
    return true;
  }
  return false;
}

bool AdjacencyMatrixGraph::RemoveNode(unsigned node)
{
  if (IsNodeExsist(node)) {
    // remove 'node id' in row
    for (auto& element : matrix_[node]) {
      element = INFINITE;
    }
    // remove 'node_idx' in column
    for (auto& rows : matrix_) {
      rows[node] = INFINITE;
    }
    return true;
  }
  return false;
}

bool AdjacencyMatrixGraph::AddEdge(unsigned base_node, unsigned target_node, int weight)
{
  if (IsNodeExsist(base_node) && IsNodeExsist(target_node)) {
    matrix_[base_node][target_node] = weight;
  }
  return false;
}

bool AdjacencyMatrixGraph::RemoveEdge(unsigned base_node, unsigned target_node)
{
  if (IsEdgeExsist(base_node, target_node)) {
    matrix_[base_node][target_node] = INFINITE;
  }
  return false;
}

vector<unsigned> AdjacencyMatrixGraph::GetNeighbours(unsigned node) const
{
  vector<unsigned> result;
  if (IsNodeExsist(node)) {
    auto idx = node;
    auto& row = matrix_[idx];
    for (unsigned i = 0; i < row.size(); ++i) {
      if (i != idx && row[i] != 0) {
        result.push_back(i);
      }
    }
  }
  return result;
}

vector<Edge> AdjacencyMatrixGraph::GetIncidentEdges(unsigned node) const
{
  return vector<Edge>();
}

size_t AdjacencyMatrixGraph::GetNodeCount() const
{
  size_t count = 0;
  for (unsigned idx = 0; idx < capacity_; ++idx) {
    if (matrix_[idx][idx] == NODE_EXSISTS) {
      ++count;
    }
  }
  return count;
}

size_t AdjacencyMatrixGraph::GetEdgeCount() const
{
  size_t count = 0;
  for (unsigned row = 0; row < capacity_; ++row) {
    for (unsigned col = 0; col < capacity_; ++col) {
      if (row != col && matrix_[row][col] != INFINITE)
        ++count;
    }
  }
  return count;
}

bool AdjacencyMatrixGraph::IsNodeExsist(unsigned node) const
{
  if (IsCorrectNodeIdx(node)) {
    return matrix_[node][node] == NODE_EXSISTS;
  }
  return false;
}

bool AdjacencyMatrixGraph::IsEdgeExsist(unsigned base_node, unsigned target_node)
{
  if (IsNodeExsist(base_node) && IsNodeExsist(target_node) && base_node != target_node) {
    return matrix_[base_node][target_node] != INFINITE;
  }
  return false;
}

void AdjacencyMatrixGraph::SetupMatrix(size_t capacity)
{
  capacity_ = capacity;
  matrix_.resize(capacity_);
  for (unsigned i = 0; i < capacity_; ++i) {
    matrix_[i].resize(capacity_);
    for (unsigned j = 0; j < capacity_; ++j) {
      matrix_[i][j] = INFINITE;
    }
  }
}

}
// ~~ Graphene::AdjacencyMatrixGraph
