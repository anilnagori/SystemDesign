/*

10.Trie Serialization

Serialize and deserialize a trie (prefix tree, search on internet for more details).
You can specify your own serialization algorithm, the online judge only cares about whether 
you can successfully deserialize the output from your own serialize function.

Notice:
You don't have to serialize like the test data, you can design your own format.

Example:
str = serialize(old_trie)
>> str can be anything to represent a trie
new_trie = deserialize(str)
>> new_trie should have the same structure and values with old_trie
An example of test data: trie tree <a<b<e<>>c<>d<f<>>>>, denote the following structure:
     root
      /
     a
   / | \
  b  c  d
 /       \
e         f

The first thing to be clear about this question is that you can't use BFS. Because BFS takes 
up too much space, the space complexity is O(26^h), and h is the height of the tree.
Then you can only use DFS. And we know that if you want to restore the binary tree directly 
with the results of DFS, you need at least two different ways to traverse the results. Not to 
mention that this is Trie, the situation will be more complicated.

Then, a better approach is to document the complete process of DFS traversal, including the 
process from the parent node to the child node, and the process of returning the parent node 
from the child node.
In other words, it is the process of recording the changes in the stack.

Serialize:
Here use '+' to represent the stack process, '-' to indicate the stack process, then for the 
tree in example, when 'a' is accessed as a child of root, it should be added to the result string. 
"+a".
When returning 'b' from 'e', ​​a "-" should be added to the result to indicate that 
'e' is popped.
Then the process of accessing from 'e' to 'e' and then returning from 'e' to 'a' can be expressed 
as "+a+b+e--". After this is done, the rest of the stack is root and 'a ', the next one to be 
accessed is the next child node 'c' of 'a'.

Deserialize:
Restoring the entire tree only requires converting the previous results into a stack access 
process.
When a '+' is encountered, the next character is pushed onto the stack, and since it is DFS, 
the character must be a child of the current top node.
When a '-' is encountered, a node is popped.
Until the entire string is traversed.

*/

/**
 * Definition of TrieNode:
 * struct TrieNode {
 *     unordered_map<char, TrieNode*> children;
 * }
**/

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
};

class Solution {
public:
  /**
  * This method will be invoked first, you should design your own algorithm 
  * to serialize a trie which denote by a root node to a string which
  * can be easily deserialized by your own "deserialize" method later.
  */
  string serialize(TrieNode* root) {
    if (root == nullptr) {
      return "";
    }
    
    string s = "";
    
    for (auto& entry: root->children) {
      s += "+" + entry.first;
      s += serialize(entry.second);
      s += "-";
    }
    
    return s;
  }

  /**
  * This method will be invoked second, the argument data is what exactly
  * you serialized at method "serialize", that means the data is not given by
  * system, it's given by your own serialize method. So the format of data is
  * designed by yourself, and deserialize it here as you serialize it in 
  * "serialize" method.
  */
  TrieNode* deserialize(string data) {
    TrieNode* root =  new TrieNode();
    stack<TrieNode*> st;
    size_t idx = 0;
    
    st.push(root);
    
    while (idx < data.length()) {
      if (data[idx] == '+') {
          TrieNode* node =  new TrieNode();
          st.top()->children[data[++idx]] = node;
          st.push(node);
      } else if (data[idx] == '-') {
          st.pop();
      }

      idx++;
    }
    
    return root;
  }
};

