//
// Created by jun on 7/14/17.
//
#ifndef WEIGHTED_SUM_OF_COMPLETION_TIME_WEIGHTED_SUM_OF_COMPLETION_TIME_H
#define WEIGHTED_SUM_OF_COMPLETION_TIME_WEIGHTED_SUM_OF_COMPLETION_TIME_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>


/*
 * This file describes a set of jobs with positive and integral
 * weights and lengths. It has the format

 * [number_of_jobs]
 * [job_1_weight] [job_1_length]
 * [job_2_weight] [job_2_length]
 * .....
 *
 * Your task in this problem is to run the greedy algorithm that
 * schedules jobs in decreasing order of the difference
 * (weight - length). Note that this algorithm is not always optimal.
 * IMPORTANT: if two jobs have equal difference (weight - length),
 * you should schedule the job with higher weight first.
 *
 * Another task is to run the greedy algorithm that schedules jobs
 * (optimally) in decreasing order of the ratio (weight/length).
 * In this algorithm, it does not matter how you break ties.
 */

typedef std::pair<int, int> job;

//
// Define job comparison operation (by weight - length)
// Will sort in descending order.
//
bool compareJobDiffer(job jb1, job jb2) {
  int differ1 = jb1.first - jb1.second;
  int differ2 = jb2.first - jb2.second;

  if (differ1 == differ2) {
    return (jb1.first > jb2.first);
  } else {
    return (differ1 > differ2);
  }
}

//
// Define job comparison operation (by weight/length)
// Will sort in descending order.
//
bool compareJobRatio(job jb1, job jb2) {
  double ratio1 = double(jb1.first) / jb1.second;
  double ratio2 = double(jb2.first) / jb2.second;

  if (ratio1 == ratio2) {
    return (jb1.first > jb2.first);
  } else {
    return (ratio1 > ratio2);
  }
}


long long int weightedSumOfCompletionTime(const std::vector<job>& jobs) {
  long int t0 = 0;
  long long int result = 0;
  for ( auto it = jobs.begin(); it != jobs.end(); ++it ) {
    t0 += it->second;
    result += it->first*t0;
  }

  return result;
}


void runWeightedSumOfCompletionTimeAssignment()
{
  std::cout << "\n" << std::string(80, '-') << "\n"
            << "This is the 'Weighted sum of completion time assignment' in \n"
               "the Stanford's Algorithm course at Coursera"
            << "\n" << std::string(80, '-')
            << std::endl;

  std::ifstream ifs("../data/jobs.txt", std::ifstream::in);
  std::string line;

  std::vector<job> jobs;

  // the first line
  std::getline(ifs, line);
  int n_jobs = std::stoi(line);
  // the rest lines
  while (std::getline(ifs, line)) {

    std::istringstream iss(line);
    std::string number;

    iss >> number;
    int weight = std::stoi(number);
    iss >> number;
    int length = std::stoi(number);

    jobs.push_back(std::make_pair (weight, length));
  }
  ifs.close();
  assert(jobs.size() == n_jobs);

  // Weight sum of completion time (sort the job by weight - length)
  std::sort(jobs.begin(), jobs.end(), compareJobDiffer);
  assert(weightedSumOfCompletionTime(jobs) == 69119377652);
  // Weight sum of completion time (sort the job by weight / length)
  std::sort(jobs.begin(), jobs.end(), compareJobRatio);
  assert(weightedSumOfCompletionTime(jobs) == 67311454237);

  std::cout << "Passed!:)" << std::endl;
}


#endif //WEIGHTED_SUM_OF_COMPLETION_TIME_WEIGHTED_SUM_OF_COMPLETION_TIME_H
