/*

9.Mini Cassandra

Cassandra is a NoSQL storage. The structure has two-level keys.
  Level 1: rowKey. The same as hash_key or shard_key.
  Level 2: columnKey.
  Level 3: column_value
rowKey is used to hash and can not support range query. let's simplify this to a string.
columnKey is sorted and support range query. let's simplify this to integer.
column_value is a string. you can serialize any data into a string and store it in column value.
implement the following methods:
  insert(rowKey, columnKey, column_value)
  query(rowKey, column_start, column_end) // return a list of entries

Example
insert("google", 1, "haha")
query("google", 0, 1)
>> [（1, "haha")]

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

class Cassandra {
public:
  void insert(string rowKey, int columnKey, string value) {
    database[rowKey][columnKey] = value;
  }

  vector<pair<int, string>> query(string rowKey, int columnKey1, int columnKey2) {
    assert(columnKey1 <= columnKey2);  

    auto itRow = database.find(rowKey);

    if (itRow == database.end()) {
      return { };
    }

    auto itCol = itRow->second.lower_bound(columnKey1);

    vector<pair<int, string>> result;

    while (itCol != itRow->second.end() && itCol->first <= columnKey2) {
      result.push_back({itCol->first, itCol->second});
      ++itCol;
    }

    return result;
  }

private:
  unordered_map<string, map<int, string>> database;
};

int main() {
  Cassandra cassandra;

  cassandra.insert("google", 1, "haha");
  
  auto result = cassandra.query("google", 0, 1);

  for (auto& r: result) {
    cout << "col " << r.first << " value " << r.second << endl;
  }
}

