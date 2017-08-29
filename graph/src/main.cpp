//
// Created by jun on 6/19/17.
//
#include "test/unittest_graph.h"
#include "test/test_dfs.h"
#include "test/test_bfs.h"
#include "test/test_dijkstra.h"
#include "test/test_kosaraju.h"
#include "test/test_prim.h"
#include "test/test_kruskal.h"
#include "test/test_bellman_ford.h"
#include "assignments/assignment_shortest_path.h"
#include "assignments/assignment_MST.h"
#include "assignments/assignment_SCC.h"


int main() {

  graph_test::simpleUdGraph();
  graph_test::simpleGraph();
  graph_test::distanceUdGraph();
  graph_test::distanceGraph();

  graph_test::testGraphCopy();
  graph_test::testReverseGraph();
  graph_test::testBreathFirstSearch();
  graph_test::testDepthFirstSearch();
  graph_test::testDijkstra();
  graph_test::testKosaraju();
  graph_test::testPrim();
  graph_test::testKruskal();
  graph_test::testBellmanFord();
//  graph_test::testKarger();
  runShortestPathAssignment();
  runPrimAssignment();
  runSccAssignment();
//  assignment::runKargerAssignment();

  return 0;
}
