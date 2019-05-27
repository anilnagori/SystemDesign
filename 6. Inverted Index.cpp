/*

6. Inverted Index

Create an inverted index with given documents.

Notice:
Ensure that data does not include punctuation.

Example:
 
Given a list of documents with id and content. (class Document)
[
  {
    "id": 1,
    "content": "This is the content of document 1 it is very short"
  },
  {
    "id": 2,
    "content": "This is the content of document 2 it is very long bilabial bilabial heheh hahaha ..."
  },
]
Return an inverted index (HashMap with key is the word and value is a list of document ids).
{
   "This": [1, 2],
   "is": [1, 2],
   ...
}

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

class InvertedIndex {
public:
  InvertedIndex(unordered_map<int, string>& documents) {
    for (auto& document: documents) {
      int id = document.first;
      string& content = document.second;
      string token;
      stringstream ss(content);

      while (ss >> token) {
        wordToDocs[token].insert(id);
      }
    }
  }

  unordered_map<string, set<int>>& getInvertedIndexMap() {
    return wordToDocs;
  }

private:
  unordered_map<string, set<int>> wordToDocs;
};

int main() {
  unordered_map<int, string> documents;

  documents[1] = "This is the content of document 1 it is very short";
  documents[2] = "This is the content of document 2 it is very long bilabial bilabial heheh hahaha ...";

  InvertedIndex invertedIndex(documents);

  auto& indexMap = invertedIndex.getInvertedIndexMap();

  for (auto& p: indexMap) {
    cout << "word : " << p.first << endl; 
    cout << "Documents : ";

    copy(p.second.begin(), p.second.end(), ostream_iterator<int> (cout, " "));
    cout << endl;
  }
}
