#include "AdjacencyListGraph.h"

using std::size_t;
using std::vector;

namespace Graphene {

bool AdjacencyListGraph::AddNode(unsigned node)
{
  if (IsCorrectNodeIdx(node) && !IsNodeExsist(node)) {
    nodes_ex_[node] = true;
    return true;
  }
  return false;
}

bool AdjacencyListGraph::RemoveNode(unsigned node)
{
  if (IsNodeExsist(node)) {
    list_[node].clear();
    for (unsigned idx = 0; idx < capacity_; ++idx) {
      auto& row = list_[node];
      for (auto it = row.begin(); it != row.end(); ++it) {
        if (it->id == node) {
          row.erase(it);
          return true;
        } 
      }
    }
    nodes_ex_[node] = false;
    return true;
  }
  return false;
}

bool AdjacencyListGraph::AddEdge(unsigned base_node, unsigned target_node, int weight)
{
  if (IsNodeExsist(base_node) && IsNodeExsist(target_node)) {
    list_[base_node].push_back({ target_node, weight });
  }
  return false;
}

bool AdjacencyListGraph::RemoveEdge(unsigned base_node, unsigned target_node)
{
  if (IsNodeExsist(base_node) && IsNodeExsist(target_node)) {
    auto& row = list_[base_node];
    for (auto it = row.begin(); it != row.end(); ++it) {
      if (it->id == target_node) {
        row.erase(it); 
        return true;
      }
    }
  }
  return false;
}

vector<unsigned> AdjacencyListGraph::GetAdjacentNodes(unsigned node) const
{
  vector<unsigned> nodes;
  if (IsNodeExsist(node)) {
    for (auto elem : list_[node]) {
      nodes.push_back(elem.id);
    }
  }
  return nodes;
}

vector<Edge> AdjacencyListGraph::GetIncidentEdges(unsigned node) const
{
  vector<Edge> edges;
  if (IsNodeExsist(node)) {
    auto adjacent_nodes = GetAdjacentNodes(node);
    for (auto element : adjacent_nodes) {
      edges.push_back({ node, element, GetEdgeValue(node, element) });
    }
    for (unsigned idx = 0; idx < capacity_; ++idx) {
      if (idx != node) {
        auto& row = list_[idx];
        for (auto elem : row) {
          if (elem.id == node) {
            edges.push_back({ idx, node, GetEdgeValue(idx, node) });
          }
        }
      }
    }
  }
  return edges;
}

int AdjacencyListGraph::GetEdgeValue(unsigned base_node, unsigned target_node) const
{
  if (IsEdgeExsist(base_node, target_node)) {
    auto& row = list_[base_node];
    for (auto node : row) {
      if (node.id == target_node) return node.weight;
    }
  }
  return -1;
}

size_t AdjacencyListGraph::GetEdgeCount() const
{
  size_t count = 0;
  for (auto& row : list_) {
    count += row.size();
  }
  return count;
}

size_t AdjacencyListGraph::GetNodeCount() const
{
  size_t count = 0;
  for (auto ex : nodes_ex_) {
    count += (ex ? 1 : 0);
  }
  return count;
}

bool AdjacencyListGraph::IsNodeExsist(unsigned node) const
{
  return IsCorrectNodeIdx(node) && nodes_ex_[node];
}

bool AdjacencyListGraph::IsEdgeExsist(unsigned base_node, unsigned target_node) const
{
  if (IsNodeExsist(base_node) && IsNodeExsist(target_node)) {
    auto& row = list_[base_node];
    for (auto node : row) {
      if (node.id == target_node) {
        return true;
      }
    }
  }
  return false;
}

void AdjacencyListGraph::SetupList(std::size_t capacity)
{
  capacity_ = capacity;
  list_.resize(capacity_);
  nodes_ex_.reserve(capacity_);
  for (unsigned idx = 0; idx < capacity_; ++idx) {
    nodes_ex_.push_back(false);
  }
}

bool AdjacencyListGraph::AreNodesAdjacent(unsigned base_node, unsigned target_node) const
{
  return IsEdgeExsist(base_node, target_node);
}

bool AdjacencyListGraph::AreNodesIncident(unsigned base_node, unsigned target_node) const
{
  return IsEdgeExsist(base_node, target_node) || IsEdgeExsist(target_node, base_node);
}

}
// ~~ Graphene::AdjacencyListGraph
