//
// Created by jun on 6/19/17.
//
#include "assignments.h"
#include "test/unittest_graph.h"
#include "test/unittest_algorithms.h"


int main() {

  graph_test::simpleUdGraph();

  graph_test::testGraphCopy();
  graph_test::testReverseGraph();
  graph_test::testBreathFirstSearch();
  graph_test::testDepthFirstSearch();

  graph_test::testKarger();
  graph_test::testKosaraju();
  graph_test::testDijkstra();
  graph_test::testPrim();
  graph_test::testBellmanFord();

  assignment::runPrimAssignment();
//  assignment::runKargerAssignment();
//  assignment::runSccAssignment();
  assignment::runDijkstraAssignment();

  return 0;
}
