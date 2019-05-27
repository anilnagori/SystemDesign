/*

7.Load Balancer

Implement a load balancer for web servers. It provide the following functionality:
    Add a new server to the cluster => add(server_id).
    Remove a bad server from the cluster => remove(server_id).
    Pick a server in the cluster randomly with equal probability => pick().

Example:
At beginning, the cluster is empty => {}.
add(1)
add(2)
add(3)
pick()
>> 1         // the return value is random, it can be either 1, 2, or 3.
pick()
>> 2
pick()
>> 1
pick()
>> 3
remove(1)
pick()
>> 2
pick()
>> 3
pick()
>> 3

*/

#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream> 
#include <cassert>

using namespace std;

class LoadBalancer {
public:
  LoadBalancer() { }
  
  void add(int serverId) {
    if (serverToIndex.count(serverId)) {
      return;
    }

    serverToIndex[serverId] = indexToServer.size();
    indexToServer.push_back(serverId);
  }

  void remove(int serverId) {
    if (serverToIndex.count(serverId)) {
      return;
    }

    int index = serverToIndex[serverId];
    int endServerId = indexToServer.back();

    indexToServer[index] = endServerId;
    serverToIndex[endServerId] = index;
    serverToIndex.erase(serverId);
    indexToServer.pop_back();
  }

  int pick() {
    int index = random() % indexToServer.size();

    return indexToServer[index];
  }

private:
  unordered_map<int, int> serverToIndex;
  vector<int> indexToServer;
};

int main() {
  LoadBalancer loadBalancer;

  loadBalancer.add(1);
  loadBalancer.add(2);
  loadBalancer.add(3);

  cout << "pick " << loadBalancer.pick() << endl;
  cout << "pick " << loadBalancer.pick() << endl;
  cout << "pick " << loadBalancer.pick() << endl;
  cout << "pick " << loadBalancer.pick() << endl;

  loadBalancer.remove(1);

  cout << "pick " << loadBalancer.pick() << endl;
  cout << "pick " << loadBalancer.pick() << endl;
  cout << "pick " << loadBalancer.pick() << endl;
}


