//
// Created by jun on 6/19/17.
//

#include "assignments.h"
#include "my_unit_test.h"


int main() {

  my_test::test_karger();
  my_test::test_kosaraju();
  my_test::test_dijkstra();

  assignment::runKargerAssignment();
  assignment::runSccAssignment();
  assignment::runDijkstraAssignment();

  return 0;
}