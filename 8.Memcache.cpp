/*

8.Memcache 

Implement memcache which support the following features:

- get(currTime, key). Get the key's value, return 2147483647 if key does not exist.
- set(currTime, key, value, ttl). Set the key-value pair in memcache with a time to live (ttl). 
  The key will be valid from currTime to currTime + ttl - 1 and it will be expired after ttl 
  seconds. if ttl is 0, the key lives forever until out of memory.
- remove(currTime, key). Delete the key.
- incr(currTime, key, delta). Increase the key's value by delta return the new value. Return 
  2147483647 if key does not exist.
- decr(currTime, key, delta). Decrease the key's value by delta return the new value. Return 
  2147483647 if key does not exist.

It's guaranteed that the input is given with increasing currTime.

Clarification:
Actually, a real memcache server will evict keys if memory is not sufficient, and it also 
supports variety of value types like string and integer. In our case, let's make it simple, 
we can assume that we have enough memory and all of the values are integers.

Search "LRU" & "LFU" on google to get more information about how memcache evict data.
Try the following problem to learn LRU cache:
http://www.lintcode.com/problem/lru-cache

Example
get(1, 0)
>> 2147483647
set(2, 1, 1, 2)
get(3, 1)
>> 1
get(4, 1)
>> 2147483647
incr(5, 1, 1)
>> 2147483647
set(6, 1, 3, 0)
incr(7, 1, 1)
>> 4
decr(8, 1, 1)
>> 3
get(9, 1)
>> 3
delete(10, 1)
get(11, 1)
>> 2147483647
incr(12, 1, 1)
>> 2147483647

*/

/*
  Implement LRU cache with the following additional features:
  1. Evict expired data 
  2. Api to increase and decrease data for a given key
  3. Delete data explictly
*/

#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <string>
#include <list>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream> 
#include <cassert>
#include <climits>

using namespace std;

class Memcache {
public:
  Memcache(int capacity) : capacity(capacity) { }


  // Get value for key
  int get(int currTime, int key) {
    // Return max value if node is not found
    if (!lookup.count(key)) {
      return INT_MAX;
    }

    // Get list node
    auto it = lookup[key];

    // Remove if expired
    if (currTime >= it->validTime) {
      remove(it);
      return INT_MAX;
    }

    // Move node to the beginning of linked list
    // No need to update lookup as node is spliced
    orderList.splice(orderList.begin(), orderList, it);

    return it->value;
  }

  // Set value for key
  void set(int currTime, int key, int value, int timeToLive) {
    if (timeToLive == 0) {
      timeToLive = INT_MAX;
    }

    auto it = lookup.find(key);

    if (it != lookup.end()) {
      // Already exists so update value and life time
      it->second->value = value;
      it->second->validTime = currTime + timeToLive;

      // Move to the front of queue
      orderList.splice(orderList.begin(), orderList, it->second);
    } else {
      // Exceeds capacity so remove LRU node
      if (lookup.size() == capacity) {
        remove(prev(orderList.end()));
      }

      // Add a new node
      Node node(key, value, timeToLive == INT_MAX ? timeToLive : currTime + timeToLive);

      orderList.insert(orderList.begin(), node);
      lookup[key] = orderList.begin();
    }
  }

  // Remove key
  void remove(int currTime, int key) {
    auto it = lookup.find(key);

    if (it == lookup.end()) {
      return;
    }

    remove(it->second);
  }

  // Increment key value
  int incr(int currTime, int key, int value) {
    return update(currTime, key, value);
  }

  // Decrement key value
  int decr(int currTime, int key, int value) {
    return update(currTime, key, -value);
  }

private:
  // List node
  struct Node {
    Node(int key, int value, int validTime) : key(key), value(value), validTime(validTime) { }
    int key;
    int value;
    int validTime;
  };

  typedef list<Node>::iterator NodeListIter;

  // Update value
  int update(int currTime, int key, int value) {
    auto it = lookup.find(key);

    if (it == lookup.end()) {
      return INT_MAX;
    }

    if (currTime >= it->second->validTime) {
      remove(it->second);
      return INT_MAX;
    }

    it->second->value += value;
    orderList.splice(orderList.begin(), orderList, it->second);

    return it->second->value;
  }

  // Remove node
  void remove(NodeListIter it) {
    lookup.erase(it->key);
    orderList.erase(it);
  }

  size_t capacity;
  list<Node> orderList;
  unordered_map<int, NodeListIter> lookup; 
};

int main() {
  cout << "test cache 1" << endl;

  Memcache memcache(10);

  cout << memcache.get(1, 0) << endl;
  memcache.set(2, 1, 1, 2);
  cout << memcache.get(3, 1) << endl;
  cout << memcache.get(4, 1) << endl;
  cout << memcache.incr(5, 1, 1) << endl;
  memcache.set(6, 1, 3, 0);
  cout << memcache.incr(7, 1, 1) << endl;
  cout << memcache.decr(8, 1, 1) << endl;
  cout << memcache.get(9, 1) << endl;
  memcache.remove(10, 1);
  cout << memcache.get(11, 1) << endl;
  cout << memcache.incr(12, 1, 1) << endl;
  cout << memcache.get(100, 1) << endl;

  cout << "test cache 2" << endl;

  Memcache memcache2(1);
  cout << memcache2.get(1, 0) << endl;
  memcache2.set(2, 1, 3, 6);
  cout << memcache2.get(3, 1) << endl;
  memcache2.set(4, 2, 4, 2);
  cout << memcache2.get(5, 1) << endl;
  cout << memcache2.get(5, 2) << endl;
}
