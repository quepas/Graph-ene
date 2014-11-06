#include <catch.hpp>

#include "AdjacencyListGraph.h"

using Graphene::AdjacencyListGraph;

TEST_CASE("Basic graph manipulation") {
  SECTION("Adding and removing nodes") {
    AdjacencyListGraph graph;

    REQUIRE(graph.GetNodeCount() == 0);
    graph.AddNode(1);
    graph.AddNode(2);
    graph.AddNode(3);
    REQUIRE(graph.GetNodeCount() == 3);
    REQUIRE(graph.IsNodeExsist(-1) == false);
    REQUIRE(graph.IsNodeExsist(1));
    REQUIRE(graph.IsNodeExsist(2));
    REQUIRE(graph.IsNodeExsist(3));
    REQUIRE(graph.IsNodeExsist(4) == false);
    REQUIRE(graph.IsNodeExsist(AdjacencyListGraph::INITIAL_CAPACITY) == false);
    REQUIRE(graph.RemoveNode(1));
    REQUIRE(graph.RemoveNode(4) == false);
    REQUIRE(graph.RemoveNode(-1) == false);
    REQUIRE(graph.GetNodeCount() == 2);
    REQUIRE(graph.IsNodeExsist(4) == false);
    graph.AddNode(1);
    graph.AddNode(2);
    graph.AddNode(3);
    REQUIRE(graph.GetNodeCount() == 3);
    REQUIRE(graph.IsNodeExsist(1));
    REQUIRE(graph.IsNodeExsist(2));
    REQUIRE(graph.IsNodeExsist(3));
  }

  SECTION("Adding and removing edges") {
    AdjacencyListGraph graph;

    graph.AddNode(1);
    graph.AddNode(2);
    graph.AddNode(3);
    REQUIRE(graph.GetNodeCount() == 3);

    REQUIRE(graph.IsEdgeExsist(1, 3) == false);
    REQUIRE(graph.IsEdgeExsist(2, 3) == false);
    graph.AddEdge(1, 3, 100);
    graph.AddEdge(2, 3, 150);
    REQUIRE(graph.GetNodeCount() == 3);
    REQUIRE(graph.GetEdgeCount() == 2);
    REQUIRE(graph.IsEdgeExsist(1, 3));
    REQUIRE(graph.IsEdgeExsist(2, 3));

    graph.RemoveEdge(1, 3);
    REQUIRE(graph.GetEdgeCount() == 1);
    REQUIRE(graph.IsEdgeExsist(1, 3) == false);
    graph.RemoveEdge(3, 1);
    REQUIRE(graph.GetEdgeCount() == 1);
    REQUIRE(graph.IsEdgeExsist(3, 1) == false);
  }

  SECTION("Checking existence and correctness of nodes/edges") {
    AdjacencyListGraph graph;

    graph.AddNode(1);
    graph.AddNode(3);
    /*REQUIRE(graph.IsCorrectNodeIdx(-1) == false);
    REQUIRE(graph.IsCorrectNodeIdx(0));
    REQUIRE(graph.IsCorrectNodeIdx(1));
    REQUIRE(graph.IsCorrectNodeIdx(2));
    REQUIRE(graph.IsCorrectNodeIdx(3));
    REQUIRE(graph.IsCorrectNodeIdx(AdjacencyListGraph::INITIAL_CAPACITY) == false); */

    REQUIRE(graph.IsNodeExsist(-1) == false);
    REQUIRE(graph.IsNodeExsist(1));
    REQUIRE(graph.IsNodeExsist(2) == false);
    REQUIRE(graph.IsNodeExsist(3));
    REQUIRE(graph.IsNodeExsist(AdjacencyListGraph::INITIAL_CAPACITY) == false);

    REQUIRE(graph.IsEdgeExsist(-1, -1) == false);
    REQUIRE(graph.IsEdgeExsist(1, 1) == false);
    REQUIRE(graph.IsEdgeExsist(1, 3) == false);
    REQUIRE(graph.IsEdgeExsist(3, 1) == false);
    REQUIRE(graph.IsEdgeExsist(3, 3) == false);

    graph.AddEdge(1, 3, 100);
    REQUIRE(graph.IsEdgeExsist(1, 3));
    REQUIRE(graph.IsEdgeExsist(1, 1) == false);
    REQUIRE(graph.IsEdgeExsist(3, 1) == false);
    REQUIRE(graph.IsEdgeExsist(3, 3) == false);
  }

  SECTION("Checking for neighboring edges/nodes") {
    AdjacencyListGraph graph;

    graph.AddNode(1);
    graph.AddNode(2);
    graph.AddNode(3);

    REQUIRE(graph.GetAdjacentNodes(-1).size() == 0);
    REQUIRE(graph.GetAdjacentNodes(1).size() == 0);
    REQUIRE(graph.GetAdjacentNodes(2).size() == 0);
    REQUIRE(graph.GetAdjacentNodes(3).size() == 0);
    REQUIRE(graph.GetAdjacentNodes(AdjacencyListGraph::INFINITE).size() == 0);

    graph.AddEdge(1, 2, 120);
    graph.AddEdge(1, 3, 130);
    graph.AddEdge(2, 3, 230);
    auto neighbours = graph.GetAdjacentNodes(1);
    REQUIRE(neighbours.size() == 2);
    REQUIRE(neighbours[0] == 2);
    REQUIRE(neighbours[1] == 3);
    neighbours = graph.GetAdjacentNodes(2);
    REQUIRE(neighbours.size() == 1);
    REQUIRE(neighbours[0] == 3);
    REQUIRE(graph.GetAdjacentNodes(3).size() == 0);

    auto incidence_edges = graph.GetIncidentEdges(1);
    REQUIRE(incidence_edges.size() == 2);
    REQUIRE(incidence_edges[0].base_node == 1);
    REQUIRE(incidence_edges[0].target_node == 2);
    REQUIRE(incidence_edges[0].weight == 120);
    REQUIRE(incidence_edges[1].base_node == 1);
    REQUIRE(incidence_edges[1].target_node == 3);
    REQUIRE(incidence_edges[1].weight == 130);

    incidence_edges = graph.GetIncidentEdges(2);
    REQUIRE(incidence_edges.size() == 2);
    REQUIRE(incidence_edges[0].base_node == 2);
    REQUIRE(incidence_edges[0].target_node == 3);
    REQUIRE(incidence_edges[0].weight == 230);
    REQUIRE(incidence_edges[1].base_node == 1);
    REQUIRE(incidence_edges[1].target_node == 2);
    REQUIRE(incidence_edges[1].weight == 120);

    incidence_edges = graph.GetIncidentEdges(3);
    REQUIRE(incidence_edges.size() == 2);
    REQUIRE(incidence_edges[0].base_node == 1);
    REQUIRE(incidence_edges[0].target_node == 3);
    REQUIRE(incidence_edges[0].weight == 130);
    REQUIRE(incidence_edges[1].base_node == 2);
    REQUIRE(incidence_edges[1].target_node == 3);
    REQUIRE(incidence_edges[1].weight == 230);
  }
}