#include <catch.hpp>

#include "AdjacencyMatrixGraph.h"

using Graphene::AdjacencyMatrixGraph;

TEST_CASE("Basic graph manipulation") {
  SECTION("Adding and removing nodes") {
    AdjacencyMatrixGraph graph;

    REQUIRE(graph.GetNodeCount() == 0);
    graph.AddNode(1);
    graph.AddNode(2);
    graph.AddNode(3);
    REQUIRE(graph.GetNodeCount() == 3);
    REQUIRE(graph.IsNodeExsist(1));
    REQUIRE(graph.IsNodeExsist(2));
    REQUIRE(graph.IsNodeExsist(3));
    REQUIRE(graph.IsNodeExsist(4) == false);
    graph.RemoveNode(1);
    graph.RemoveNode(4);
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
    AdjacencyMatrixGraph graph;

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
    AdjacencyMatrixGraph graph;

    graph.AddNode(1);
    graph.AddNode(3);
    REQUIRE(graph.IsCorrectNodeIdx(-1) == false);
    REQUIRE(graph.IsCorrectNodeIdx(0));
    REQUIRE(graph.IsCorrectNodeIdx(1));
    REQUIRE(graph.IsCorrectNodeIdx(2));
    REQUIRE(graph.IsCorrectNodeIdx(3));
    REQUIRE(graph.IsCorrectNodeIdx(AdjacencyMatrixGraph::INITIAL_CAPACITY) == false);

    REQUIRE(graph.IsNodeExsist(-1) == false);
    REQUIRE(graph.IsNodeExsist(1));
    REQUIRE(graph.IsNodeExsist(2) == false);
    REQUIRE(graph.IsNodeExsist(3));
    REQUIRE(graph.IsNodeExsist(AdjacencyMatrixGraph::INITIAL_CAPACITY) == false);

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
}