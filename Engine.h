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
using std::make_move_iterator;
using std::string;
using std::to_string;
using std::cout;
using std::cin;
using std::endl;
using std::pair;
using std::numeric_limits;

class Engine {
  public:
    Engine();
    void input();
    void augmentedBestFit();
    void nextFit();
    void output();

    struct job {
      int size = 0;
      string name = "Default";
      string status = "Wait";
    };

    struct partition {
      int size = 0;
      int space = 0;
      vector<job> partitioned_jobs;
    };

    int partition_count;
    int job_count;
    vector <partition> partitions;
    vector <job> jobs;
};
