//
//
// Compare the speeds of insertion, retrieving, deletion, etc. of
// std::map and std::unsorted_map.
//
// Created by jun on 7/8/17.
//
#ifndef HASH_TABLE_IMPLEMENTATION_BENCHMARK_H
#define HASH_TABLE_IMPLEMENTATION_BENCHMARK_H

#include <iostream>
#include <assert.h>
#include <random>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>


//
// Generate a vector of random integer data
//
// @param n: length of the data container
// @param factor: factor for the random number poor, i.e. the random number
//                will be generated between 0 and factor*n.
//
// @return: data
//
std::vector<int> prepareData(size_t n, double factor=1.0) {

  std::vector<int> data(n);

  std::random_device rd;
  std::default_random_engine generator(rd());
  std::uniform_int_distribution<int> uniform_dist(0, int(factor*n));

  for (size_t i=0; i<n; ++i) {
    data[i] = uniform_dist(generator);
  }

  return data;
}

//
// Test the speed of different operations of std::map()
//
// @param data: a vector
//
template <class T1, class T2>
void testMap(const std::vector<T1>& keys, const std::vector<T2>& data) {
  std::map<T1, T2> tree;

  clock_t t0 = clock();
  for (size_t i = 0; i < data.size(); ++i) {
    tree.insert(std::pair<T1, T2> (keys[i], data[i]));
  }
  std::cout << "Insertion time: "
            << 1000.0 * (clock() - t0) / CLOCKS_PER_SEC << " ms" << std::endl;

  t0 = clock();
  for (size_t i = 0; i < data.size(); ++i) {
    assert(tree[keys[i]] == data[i]);
  }
  std::cout << "Retrieve time: "
            << 1000.0 * (clock() - t0) / CLOCKS_PER_SEC << " ms" << std::endl;

  t0 = clock();
  for (size_t i = 0; i < data.size(); ++i) {
    tree.erase(keys[i]);
  }
  assert(tree.empty());
  std::cout << "Deletion time: "
            << 1000.0 * (clock() - t0) / CLOCKS_PER_SEC << " ms" << std::endl;
}

//
// Test the different operation speeds of std::unordered_map
//
// @param data: a vector
//
template <class T1, class T2>
void testUnorderedMap(const std::vector<T1>& keys, const std::vector<T2>& data,
                      double max_load_factor=1.0) {
  std::unordered_map<T1, T2> hash;
  hash.max_load_factor(max_load_factor);

  clock_t t0 = clock();
  for (size_t i = 0; i < data.size(); ++i) {
    hash.insert({keys[i], data[i]});
  }
  std::cout << "Insertion time: "
            << 1000.0*(clock() - t0)/CLOCKS_PER_SEC << " ms" << std::endl;

  std::cout << "Load factor: " << hash.load_factor() << std::endl;
  std::cout << "Max load factor: " << hash.max_load_factor() << std::endl;

  t0 = clock();
  for ( size_t i=0; i < data.size(); ++i ) {
    assert(hash[keys[i]] == data[i]);
  }
  std::cout << "Retrieve time: "
            << 1000.*(clock() - t0)/CLOCKS_PER_SEC << " ms" << std::endl;

  t0 = clock();
  for ( size_t i=0; i < data.size(); ++i ) {
    hash.erase(keys[i]);
  }
  assert(hash.empty());
  std::cout << "Deletion time: "
            << 1000.0*(clock() - t0)/CLOCKS_PER_SEC << " ms" << std::endl;
}

//
// benchmark different implementations
//
// @param n: length of the data container
//
void runBenchmark(size_t n) {

  std::vector<int> data = prepareData(n, 1.0);

  std::vector<int> keys_int(data.size());
  for ( size_t i=0; i < data.size(); ++i ) {
    keys_int[i] = i;
  }
  std::cout << "\nTest on std::map with integer keys:" << std::endl;
  testMap(keys_int, data);
  std::cout << "\nTest on std::unordered_map with integer keys: " << std::endl;
  testUnorderedMap(keys_int, data, 0.2);

  std::vector<std::string> keys_string(data.size());
  for ( size_t i=0; i < data.size(); ++i ) {
    keys_string[i] = std::to_string(i);
  }
  std::cout << "\nTest on std::map with string keys:" << std::endl;
  testMap(keys_string, data);
  std::cout << "\nTest on std::unordered_map with string keys: " << std::endl;
  testUnorderedMap(keys_string, data, 0.2);
}

#endif //HASH_TABLE_IMPLEMENTATION_BENCHMARK_H
