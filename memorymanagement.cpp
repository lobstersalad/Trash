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
using std::string;
using std::to_string;
using std::cout;
using std::cin;
using std::endl;
using std::pair;
using std::numeric_limits;

/* Things one could add if one cared enough
   - Input validation
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
  int space = 0;
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
      partitions[i].space = partitions[i].size;
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

  vector <job> jobs_copy = jobs;
  int current_best = numeric_limits<int>::max();
  pair<string, int> candidate; // <job, partition>

  // Find the current best fit candidate and place it into selected partition
  do {
    candidate.second = -1;
    for (int i = 0; i < jobs.size(); i++) {
      for (int j = 0; j < partitions.size(); j++) {
        int difference = partitions[j].space - jobs[i].size;
        if (difference > -1 && difference < current_best) {
          current_best = difference;
          candidate.first = jobs[i].name;
          candidate.second = j;
        }
      }
    }

    // Move candidate from jobs list to selected partition
    string name = candidate.first;
    vector<job>::iterator it = find_if(jobs.begin(), jobs.end(), [&name](job& object) {
      return object.name == name;
    });
    if (it != jobs.end()) {
      partitions[candidate.second].space -= it->size;
      partitions[candidate.second].partitioned_jobs.push_back(*it);
      jobs.erase(it);
    } else {
      break;
    }

    current_best = numeric_limits<int>::max();
  } while (jobs.size() > 0 && candidate.second != -1);

  // Show algorithm results
  cout << "\nResults: " << endl;
  for (int i = 0; i < partitions.size(); i++) {
    cout << "Partition " << i + 1 << ": " << partitions[i].space << " / " << partitions[i].size << " space available" << endl;
    cout << "Contents: ";
    for (int j = 0; j < partitions[i].partitioned_jobs.size(); j++) {
      cout << "<" << partitions[i].partitioned_jobs[j].name << ", " << partitions[i].partitioned_jobs[j].size << "> ";
    }
    cout << endl;
  }

  cout << "\nUnassigned Jobs:\n";
  for (int i = 0; i < jobs.size(); i++) {
    cout << "<" << jobs[i].name << ", " << jobs[i].size << ">" << endl;
  }

  return 0;
}
