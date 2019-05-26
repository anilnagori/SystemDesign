/*

2.Consistent Hashing II

In Consistent Hashing I we introduced a relatively simple consistency hashing algorithm. 
This simple version has two drawbacks:
- After adding a machine, the data comes from one of the machines. The read load of this 
  machine is too large, which will affect the normal service.
- When added to 3 machines, the load of each server is not balanced, it is 1:1:2.

To solve this problem, the concept of micro-shards was introduced. A better algorithm is this:

Divide the 360° interval to be finer. Change from 0~359 to a range of 0~n-1, and connect 
the sections end to end, and connect them into a circle. When joining a new machine, randomly 
choose to sprinkle k points in the circle, representing the k micro-shards of the machine.

Each data also corresponds to a point on the circumference, which is calculated by a hash 
function.

A data belongs to the machine that is responsible for management, and is determined by the 
machine to which the first micro-shard point touched clockwise on the circle corresponding 
to the point on the circumference of the data. n and k are typically 2^64 and 1000 in a 
real NoSQL database.

Implement this method that introduces a micro-shard's consistent hashing. The main implementation 
of the following three functions:

create(int n, int k)
addMachine(int machine_id) // add a new machine, return a list of shard ids.
getMachineIdByHashCode(int hashcode) // return machine id

Notice:
When n is 2^64, there is basically no repetition in the interval within this interval.
But to make it easier to test the correctness of your program, n may be smaller in the data, so 
you must ensure that the k random numbers you generate do not duplicate.
LintCode does not judge the correctness of your returnMachine's return (because it is a random 
number), it will only judge the correctness of your getMachineIdByHashCode result based on the 
result of the addMachine you return.

Example:
create(100, 3)
addMachine(1)
>> [3, 41, 90] => Three random numbers
getMachineIdByHashCode(4)
>> 1
addMachine(2)
>> [11, 55, 83]
getMachineIdByHashCode(61)
>> 2
getMachineIdByHashCode(91)
>> 1
*/

#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <cassert>

using namespace std;

// Generate randome number in a given range
// Number are not repeated until all numbers are used
class RandomNumGenerator {
public:
  RandomNumGenerator(int t) : maxRange(t), range(maxRange) { }

  // Get next random number in the range [0, range)
  int getRandom() {
    if (!freeNumList.empty()) {
      int val = freeNumList.back();
      freeNumList.pop_back();
      return val;
    }

    // Reinit if the all random number are geneared once in [0, maxRange)
    if (!range) {
      reinit();
    }

    // Generate a random index in range [0, range)
    int ri = random() % range;
    int val = holes.count(ri) ? holes[ri] : ri;
    
    --range;

    // If there is a hole at range then move it to ri
    holes[ri] = holes.count(range) ? holes[range] : range;

    return val;
  }

  void freeNum(int n) {
    assert(n < maxRange);
    freeNumList.push_back(n);
  }

  void reinit() {
    range = maxRange;
    holes.clear();
  }

private:
  const int maxRange;
  int range;
  unordered_map<int, int> holes;
  vector<int> freeNumList;
};

class ConsistentHashing {
public:
  ConsistentHashing(int n, int k) : 
    maxNumShards(n), 
    numShardsAvailable(n), 
    numShardsPerMachine(k), 
    randomNumGenerator(n) {
  }

  vector<int> addMachine(int machineId) {
    assert(machineId >= 0);

    if (numShardsPerMachine > numShardsAvailable) {
      return { };
    }

    vector<int> shards;
    int i = numShardsPerMachine;

    shards.reserve(numShardsPerMachine);

    while (i) {
      int shard = randomNumGenerator.getRandom();
      shardToMachine[shard] = machineId;
      shards.push_back(shard);
      --i;
    }

    machineToShards[machineId] = shards;

    return shards;
  }

  void removeMachine(int machineId) {
    auto it = machineToShards.find(machineId);

    if (it == machineToShards.end()) {
      return;
    }

    for (int shard: it->second) {
      randomNumGenerator.freeNum(shard);
      shardToMachine.erase(shard);
    }

    it->second.clear();
    machineToShards.erase(it);
  }

  int getMachineFromHashCode(int hashCode) {
    assert(hashCode < maxNumShards);
    
    if (shardToMachine.empty()) {
      return -1;
    }

    auto it = shardToMachine.lower_bound(hashCode);

    if (it == shardToMachine.end()) {
      it = shardToMachine.lower_bound(0);
    }

    return it->second;
  }

private:
  int maxNumShards;
  int numShardsAvailable;
  int numShardsPerMachine;
  map<int, int> shardToMachine;
  unordered_map<int, vector<int>> machineToShards;
  RandomNumGenerator randomNumGenerator;
};

int main() {
  ConsistentHashing consistentHashing(100, 5);

  for (int m: {1, 2, 3, 4}) {
    auto shards = consistentHashing.addMachine(m);
    cout << "machine " << m << " shards ";
    copy(shards.begin(), shards.end(), ostream_iterator<int>(cout, ", "));
    cout << endl;
  }

  for (int j = 1; j < 20; ++j) {
    int hashCode = random() % 100;
    cout << "hash code " << hashCode << " machine id " << consistentHashing.getMachineFromHashCode(hashCode) << endl;
  }

  for (int m: {1, 2, 3, 4}) {
    consistentHashing.removeMachine(m);
  }

  for (int m: {1, 2, 3, 4}) {
    auto shards = consistentHashing.addMachine(m);
    copy(shards.begin(), shards.end(), ostream_iterator<int>(cout, ", "));
    cout << endl;
  }
}
