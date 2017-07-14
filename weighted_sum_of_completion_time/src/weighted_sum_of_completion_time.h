//
// Created by jun on 7/14/17.
//

#ifndef WEIGHTED_SUM_OF_COMPLETION_TIME_WEIGHTED_SUM_OF_COMPLETION_TIME_H
#define WEIGHTED_SUM_OF_COMPLETION_TIME_WEIGHTED_SUM_OF_COMPLETION_TIME_H

/*
 * This file describes a set of jobs with positive and integral weights
 * and lengths. It has the format

 * [number_of_jobs]
 * [job_1_weight] [job_1_length]
 * [job_2_weight] [job_2_length]
 * .....
 *
 * Your task now is to run the greedy algorithm that schedules jobs
 * (optimally) in decreasing order of the ratio (weight/length).
 * In this algorithm, it does not matter how you break ties. You should
 * report the sum of weighted completion times of the resulting schedule.
 */

typedef std::pair<int, int> job;


bool compareJobDiffer(job jb1, job jb2)
{
  int differ1 = jb1.first - jb1.second;
  int differ2 = jb2.first - jb2.second;

  if (differ1 == differ2) {
    return (jb1.first > jb2.first);
  }
  else
  {
    return (differ1 > differ2);
  }
}


bool compareJobRatio(job jb1, job jb2)
{
  int ratio1 = jb1.first / jb1.second;
  int ratio2 = jb2.first / jb2.second;

  if (ratio1 == ratio2) {
    return (jb1.first > jb2.first);
  }
  else
  {
    return (ratio1 > ratio2);
  }
}


long int weightedSumOfCompletionTime(std::vector<job> jobs)
{
  int t0 = 0;
  long int result = 0;
  for ( auto it = jobs.begin(); it != jobs.end(); ++it )
  {
    t0 += it->second;
    result += it->first*t0;
  }

  return result;
}


void runWeightedSumOfCompletionTimeAssignment()
{
  std::cout << "\n" << std::string(80, '-') << "\n"
            << "This is the Weighted Sum of Completion time assignment\n"
                "in the Stanford's Algorithm course at Coursera"
            << "\n" << std::string(80, '-') << "\n"
            << std::endl;

  std::ifstream ifs("../data/jobs.txt", std::ifstream::in);
  std::string line;

  std::vector<job> jobs;

  bool flag = true;
  while (std::getline(ifs, line))
  {
    // skip the first line
    if ( flag )
    {
      flag = false;
      continue;
    }
    std::istringstream iss(line);

    std::string number;

    int count = 0;
    int weight;
    int length;
    while ( iss >> number )
    {
      ++count;
      if ( count == 1 )
      {
        weight = std::stoi(number);
      }
      else if ( count == 2 )
      {
        length = std::stoi(number);
      }
      else
      {
        continue;
      }
      jobs.push_back(std::make_pair (weight, length));
    }
  }

  std::cout << "Weight sum of complemention time using method 1 (sort the job by weight - length) is: " << std::endl;
  std::sort(jobs.begin(), jobs.end(), compareJobDiffer);
  std::cout << weightedSumOfCompletionTime(jobs) << std::endl;
  std::cout << "Weight sum of complemention time: ";
  std::sort(jobs.begin(), jobs.end(), compareJobRatio);
  std::cout << weightedSumOfCompletionTime(jobs) << std::endl;
}


#endif //WEIGHTED_SUM_OF_COMPLETION_TIME_WEIGHTED_SUM_OF_COMPLETION_TIME_H
