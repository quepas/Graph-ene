#include "AdjacencyMatrixGraph.h"

using std::size_t;
using std::vector;

namespace Graphene {

bool AdjacencyMatrixGraph::AddNode(unsigned node)
{
  if (IsCorrectNodeIdx(node) && !IsNodeExsist(node)) {
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

vector<unsigned> AdjacencyMatrixGraph::GetAdjacentNodes(unsigned node) const
{
  vector<unsigned> nodes;
  if (IsNodeExsist(node)) {
    auto& row = matrix_[node];
    for (unsigned i = 0; i < capacity_; ++i) {
      if (i != node && row[i] != INFINITE) {
        nodes.push_back(i);
      }
    }
  }
  return nodes;
}

vector<Edge> AdjacencyMatrixGraph::GetIncidentEdges(unsigned node) const
{
  vector<Edge> edges;
  if (IsNodeExsist(node)) {
    auto adjacent_nodes = GetAdjacentNodes(node);
    for (auto element : adjacent_nodes) {
      edges.push_back({ node, element, GetEdgeValue(node, element) });
    }
    for (unsigned idx = 0; idx < capacity_; ++idx) {
      if (idx != node && matrix_[idx][node] != INFINITE) {
        edges.push_back({ idx, node, GetEdgeValue(idx, node) });
      }
    }
  }
  return edges;
}

int AdjacencyMatrixGraph::GetEdgeValue(unsigned base_node, unsigned target_node) const
{
  return IsEdgeExsist(base_node, target_node) ? matrix_[base_node][target_node] : -1;
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

bool AdjacencyMatrixGraph::IsEdgeExsist(unsigned base_node, unsigned target_node) const
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

bool AdjacencyMatrixGraph::AreNodesAdjacent(unsigned base_node, unsigned target_node) const
{
  return IsEdgeExsist(base_node, target_node);
}

bool AdjacencyMatrixGraph::AreNodesIncident(unsigned base_node, unsigned target_node) const
{
  return IsEdgeExsist(base_node, target_node) || IsEdgeExsist(target_node, base_node);
}

vector<unsigned> AdjacencyMatrixGraph::GetNodes() const
{
  vector<unsigned> nodes;
  for (unsigned idx = 0; idx < capacity_; ++idx) {
    if (IsNodeExsist(idx)) nodes.push_back(idx);
  }
  return nodes;
}

vector<Edge> AdjacencyMatrixGraph::GetEdges() const
{
  vector<Edge> edges;
  auto nodes = GetNodes();
  for (auto node : nodes) {
    auto adjacent_edges = GetAdjacentEdges(node);
    edges.assign(adjacent_edges.begin(), adjacent_edges.end());
  }
  return edges;
}

std::vector<Edge> AdjacencyMatrixGraph::GetAdjacentEdges(unsigned node) const
{
  vector<Edge> edges;
  if (IsNodeExsist(node)) {
    auto adjacent_nodes = GetAdjacentNodes(node);
    for (auto element : adjacent_nodes) {
      edges.push_back({ node, element, GetEdgeValue(node, element) });
    }
  }
  return edges;
}

}
// ~~ Graphene::AdjacencyMatrixGraph
