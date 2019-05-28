/*

10.Trie Service

Build tries from a list of pairs. Save top 10 for each node.

Example:
Given a list of
<"abc", 2>
<"ac", 4>
<"ab", 9>

Return <a[9,4,2]<b[9,2]<c[2]<>>c[4]<>>>, and denote the following tree structure:
         Root
         / 
       a(9,4,2)
      /    \
    b(9,2) c(4)
   /
 c(2)
 
Put the input words into the tree and insert them into the top10 List in order of 
increasing size.

If the top10 List size is greater than 10, the last element is deleted.

*/

#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <string>
#include <list>
#include <stack>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream> 
#include <cassert>
#include <climits>

using namespace std;

struct TrieNode {
  unordered_map<char, TrieNode*> children;
  set<int> indices;
};

class TrieService {
public:
  // @param word a string
  // @param frequency an integer
  void insert(string word, int frequency) {
    TrieNode* curr = &root;
    
    for (char c : word) {
      int idx = c - 'a';

      if (!curr->children[idx]) {
        curr->children[idx] =  new TrieNode();
      }
      
      curr = curr->children[idx];
      curr->indices.insert(frequency);

      if (curr->indices.size() == 11) {
        curr->indices.erase(curr->indices.begin());
      }
    }
  }

private:
  TrieNode root;
};

