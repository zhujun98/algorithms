#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>
#include <assert.h>

#include "Huffman.h"


/*
 * This file describes an instance of the Huffman coding problem.
 * It has the following format:
 *
 * [number_of_symbols]
 *
 * [weight (frequency) of symbol #1]
 *
 * [weight (frequency) of symbol #2]
 *
 * ...
 *
 * For example, the third line of the file is "6852892," indicating
 * that the weight of the second symbol of the alphabet is 6852892.
 *
 * Your task in this problem is to run the Huffman coding algorithm on
 * this data set. What is the minimum and maximum length of a codeword i
 * n the resulting Huffman code?
 *
 * Answer: 9 and 19.
 */
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
  ifs >> number; // skip the first line

  int index = 0;
  while ( ifs >> number ) {
    ++index;
    weights.push_back(number);
    values.push_back(index);
  }

  ifs.close();
  std::cout << "Read in " << index << " numbers!" << std::endl;

  Huffman huffman;

  huffman.buildTree(values, weights);
  huffman.printTree();

  assert(huffman.minDepth() == 9);
  assert(huffman.maxDepth() == 19);
  std::cout << "Passed!" << std::endl;
}

/*
 * The output tree looks like below:
 *
 *                 /\
 *                /  \
 *               3   /\
 *                  2  \
 *                     /\
 *                    0  1
 */
 void testHuffmanCoding() {
  std::vector<int> values = {0, 1, 2, 3};
  std::vector<int> frequencies = {1, 2, 3, 4};
  Huffman huffman;
  huffman.buildTree(values, frequencies);
  huffman.printTree();
  assert(huffman.minDepth() == 1);
  assert(huffman.maxDepth() == 3);

  std::cout << "Passed test case!" << std::endl;
}

int main() {
  testHuffmanCoding();
  runHuffmanCodingAssignment();
  return 0;
}