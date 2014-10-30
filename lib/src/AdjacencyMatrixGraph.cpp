#include "AdjacencyMatrixGraph.h"

using std::size_t;
using std::vector;

namespace Graphene {

bool AdjacencyMatrixGraph::IsNodeExsist(unsigned node)
{
  if (IsCorrectNode(node)) {
    return matrix_[node][node] == NODE_EXSISTS;
  }
  return false;
}

bool AdjacencyMatrixGraph::IsEdgeExsist(unsigned base_node, unsigned target_node)
{
  if (IsNodeExsist(base_node) && IsNodeExsist(target_node)) {
    return matrix_[base_node][target_node] != INFINITE;
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
      matrix_[i][j] = INFINITE;
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

bool AdjacencyMatrixGraph::RemoveEdge(unsigned base_node, unsigned target_node)
{
  if (IsEdgeExsist(base_node, target_node)) {
    matrix_[base_node][target_node] = INFINITE;
    --edge_count_;
  }
  return false;
}

bool AdjacencyMatrixGraph::AddEdge(unsigned base_node, unsigned target_node, int weight)
{
  if (IsNodeExsist(base_node) && IsNodeExsist(target_node)) {
    matrix_[base_node][target_node] = weight;
    ++edge_count_;
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

bool AdjacencyMatrixGraph::AddNode(unsigned node)
{
  if (IsCorrectNode(node)) {
    matrix_[node][node] = NODE_EXSISTS;
    return true;
  }
  return false;
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

}
// ~~ Graphene::AdjacencyMatrixGraph
