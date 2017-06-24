//
// Created by jun on 6/19/17.
//

#include "assignments.h"
#include "unittest_graph.h"


int main() {

  my_test::testKarger();
  my_test::testKosaraju();
  my_test::testDijkstra();

  assignment::runKargerAssignment();
  assignment::runSccAssignment();
  assignment::runDijkstraAssignment();

  return 0;
}