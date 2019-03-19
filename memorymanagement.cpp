#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <limits>
#include <algorithm>
#include <stdlib.h>

using std::vector;
using std::find;
using std::move;
using std::back_inserter;
using std::string;
using std::to_string;
using std::cout;
using std::cin;
using std::endl;
using std::pair;
using std::numeric_limits;

/* Things one could add if one cared enough
   - Input validation
   - Differentiate partition available space and total size
   - Actually store job objects in partitions instead of just tracking size
   - Partition and job randomizer for testing
   - Compare execution times between algorithms
   - User defined job names with duplicates allowed
   -
*/

struct job {
  string name = "Default";
  string status = "Wait";
  int size = 0;
};

struct partition {
  int size = 0;
  vector<job> partitioned_jobs;
};

int main() {

  int partition_count, job_count;
  vector <partition> partitions;
  vector <job> jobs;

  cout << "Enter number of partitions" << endl;
  cin >> partition_count;
  partitions.resize(partition_count);

  for (int i = 0; i < partition_count; i++) {
      cout << "Enter size of partition " << i + 1 << endl;
      cin >> partitions[i].size;
  }

  cout << "Enter number of jobs" << endl;
  cin >> job_count;
  jobs.resize(job_count);

  for (int i = 0; i < job_count; i++) {
    jobs[i].name = "J" + to_string(i + 1);
    cout << "Enter a memory requirement for " << jobs[i].name << endl;
    cin >> jobs[i].size;
  }

  // Augmented Best-Fit finds best fit among all jobs instead of best fit for current job
  cout << "Running Augmented Best-Fit Algorithm" << endl;

  string name;
  vector <job> jobs_copy = jobs;
  int current_best = numeric_limits<int>::max();
  pair<string, int> candidate; // <job, partition>

  // Find the current best fit candidate and place it into selected partition
  do {
    candidate.second = -1;
    for (int i = 0; i < jobs.size(); i++) {
      for (int j = 0; j < partition_count; j++) {
        int difference = partitions[j].size - jobs[i].size;
        if (difference > -1 && difference < current_best) {
          current_best = partitions[j].size - jobs[i].size;
          candidate.first = jobs[i].name;
          candidate.second = j;
        }
      }
    }

    // Move candidate from jobs list to selected partition
    name = candidate.first;
    vector<job>::iterator it = find_if(jobs.begin(), jobs.end(), [&name](job& object) {
      return object.name == name;
    });
    if (it != jobs.end()) {
      partitions[candidate.second].size -= it->size;
      move(it, jobs.end(), back_inserter(partitions[candidate.second].partitioned_jobs));
      jobs.erase(it);
    } else {
      cout << "Candidate was not found" << endl;
      exit(EXIT_FAILURE);
    }

    current_best = numeric_limits<int>::max();
  } while (jobs.size() > 0 && candidate.second != -1);

  cout << "Printing partition contents" << endl;
  for (int i = 0; i < partitions.size(); i++) {
    cout << "Partition " << i + 1 << " available space is " << partitions[i].size << endl;
    cout << "Contents: ";
    for (int j = 0; j < partitions[i].partitioned_jobs.size(); j++) {
      cout << "<" << partitions[i].partitioned_jobs[j].name << ", " << partitions[i].partitioned_jobs[j].size << "> ";
    }
    cout << endl;
  }

  return 0;
}
