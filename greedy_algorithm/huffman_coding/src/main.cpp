#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>
#include <assert.h>

#include "Huffman.h"


void runHuffmanCodingAssignment() {
  std::cout << "\n" << std::string(80, '-') << "\n"
            << "This is the Huffman coding assignment in the \n"
            << "Stanford's Algorithm course at Coursera"
            << "\n" << std::string(80, '-')
            << std::endl;

  std::vector<int> weights;
  std::vector<int> values;

  std::ifstream ifs("../data/huffman.txt", std::ifstream::in);

  int number;
  int count = -1;
  while ( ifs >> number ) {
    ++count;
    if ( count == 0 ) { continue; } // skip the header
    weights.push_back(number);
    values.push_back(count);
  }

  ifs.close();
  std::cout << "Read in " << count << " numbers!" << std::endl;

  Huffman huffman;

  huffman.buildTree(values, weights);
  huffman.printTree();

  assert(huffman.minDepth() == 9);
  assert(huffman.maxDepth() == 19);
  std::cout << "Passed!" << std::endl;
}

void testHuffmanCoding() {
  std::vector<int> values = {0, 1, 2, 3};
  std::vector<int> frequencies = {1, 2, 3, 4};
  Huffman huffman;
  huffman.buildTree(values, frequencies);
  huffman.printTree();

}

int main() {
  std::cout << "Hello, World!" << std::endl;
  testHuffmanCoding();
  runHuffmanCodingAssignment();
  return 0;
}