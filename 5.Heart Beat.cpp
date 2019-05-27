/*

5.Heart Beat

In the Master-Slave architecture, slave server will ping master in every k seconds to tell master 
server he is alive. If a master server didn't receive any ping request from a slave server in 2 * k 
seconds, the master will trigger an alarm (for example send an email) to administrator.

Let's mock the master server, you need to implement the following three methods:
    initialize(slavesIpList, k). salves_ip_list is a list of slaves' ip addresses. k is define above.
    
    ping(timestamp, slaveIp). This method will be called every time master received a ping request from 
    one of the slave server. timestamp is the current timestamp in seconds. slaveIp is the ip address of 
    the slave server who pinged master.
    
    getDiedSlaves(timestamp). This method will be called periodically (it's not guaranteed how long between 
    two calls). timestamp is the current timestamp in seconds, and you need to return a list of slaves' ip 
    addresses that died. Return an empty list if no died slaves found.

You can assume that when the master started, the timestamp is 0, and every method will be called with an 
global increasing timestamp.

Example
initialize(["10.173.0.2", "10.173.0.3"], 10)
ping(1, "10.173.0.2")
getDiedSlaves(20)
>> ["10.173.0.3"]
getDiedSlaves(21)
>> ["10.173.0.2", "10.173.0.3"]
ping(22, "10.173.0.2")
ping(23, "10.173.0.3")
getDiedSlaves(24)
>> []
getDiedSlaves(42)
>> ["10.173.0.2"]

*/

#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <cassert>

using namespace std;

class HeartBeat {
public:
    HeartBeat() : interval(0) { }

    // @param slavesIpList a list of slaves'ip addresses
    // @param k an integer
    // @return void
    void initialize(vector<string> slavesIpList, int k) {
        for (string ip : slavesIpList) {
            slaves[ip] = 0;
        }

        interval = k;
    }

    // @param timestamp current timestamp in seconds
    // @param slaveIp the ip address of the slave server
    // @return nothing
    void ping(int timestamp, string slaveIp) {
        if (!slaves.count(slaveIp)) {
            return;
        }
        
        slaves[slaveIp] = timestamp;
    }

    // @param timestamp current timestamp in seconds
    // @return a list of slaves'ip addresses that died
    vector<string> getDiedSlaves(int timestamp) {
        vector<string> ret;
        
        for (auto& entry : slaves) {
            if (timestamp - entry.second >= 2 * interval) {
                ret.push_back(entry.first);
            }
        }

        return ret;
    }

private:
    unordered_map<string, int> slaves;
    int interval;
};

void printSlaves(vector<string>& s) {
	copy(s.begin(), s.end(), ostream_iterator<string> (cout, " "));
	cout << endl;
}

int main() {
	HeartBeat heatBest;

	heatBest.initialize({"10.173.0.2", "10.173.0.3"}, 10);
	heatBest.ping(1, "10.173.0.2");
	
	auto slaves = heatBest.getDiedSlaves(20);

	printSlaves(slaves);
	slaves = heatBest.getDiedSlaves(21);
	printSlaves(slaves);
	heatBest.ping(22, "10.173.0.2");
	heatBest.ping(23, "10.173.0.3");
	heatBest.getDiedSlaves(24);
	printSlaves(slaves);
	heatBest.getDiedSlaves(42);
	printSlaves(slaves);

}
