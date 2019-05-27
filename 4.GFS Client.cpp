/*

4.GFS Client

Implement a simple client for GFS (Google File System, a distributed file system), 
it provides the following methods:
    read(filename). Read the file with given filename from GFS.
    write(filename, content). Write a file with given filename & content to GFS.

There are two private methods that already implemented in the base class:
    readChunk(filename, chunkIndex). Read a chunk from GFS.
    writeChunk(filename, chunkIndex, chunkData). Write a chunk to GFS.

To simplify this question, we can assume that the chunk size is chunkSize bytes. (In a 
real world system, it is 64M). The GFS Client's job is splitting a file into multiple 
chunks (if need) and save to the remote GFS server. chunkSize will be given in the 
constructor. You need to call these two private methods to implement read & write methods.

Example:
GFSClient(5)
read("a.txt")
>> null
write("a.txt", "World")
>> You don't need to return anything, but you need to call writeChunk("a.txt", 0, "World") 
to write a 5 bytes chunk to GFS.
read("a.txt")
>> "World"
write("b.txt", "111112222233")
>> You need to save "11111" at chink 0, "22222" at chunk 1, "33" at chunk 2.
write("b.txt", "aaaaabbbbb")
read("b.txt")
>> "aaaaabbbbb"

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

class BaseGFSClient {
public:
  BaseGFSClient() {}

  string readChunk(string filename, int chunkIndex) {
    if (!chunks.count(filename) || !chunks[filename].count(chunkIndex)) {
      return "";
    }

    return chunks[filename][chunkIndex];
  }

  void writeChunk(string filename, int chunkIndex, string content) {
    chunks[filename][chunkIndex] = content;
  }

private:
  unordered_map<string, unordered_map<int, string>> chunks;
};

class GFSClient : public BaseGFSClient {
public:
    GFSClient(int chunkSize) : chunkSize(chunkSize) { }
    
    // @param filename a file name
    // @return conetent of the file given from GFS
    string read(string filename) {
        if (!name2Index.count(filename)) {
            return "";
        }
        
        string ret; 

        for (int i = 0; i < name2Index[filename]; i++) {
            ret += readChunk(filename, i);
        }
        
        return ret;
        
    }

    // @param filename a file name
    // @param content a string
    // @return void
    void write(string filename, string content) {
        int chunkNum = (content.length()) / chunkSize;

        if (content.length() % chunkSize) {
          ++chunkNum;
        }
        
        name2Index[filename] = chunkNum;
        
        for (int i = 0; i < chunkNum; i++) {
            int start = i * chunkSize;
            int end = min((int) content.length(), (i + 1) * chunkSize);
            writeChunk(filename, i, content.substr(start, end));
        }
    }

private:
    unordered_map<string, int> name2Index;
    int chunkSize;
};

int main() {
  GFSClient gfsClient(4);

  gfsClient.write("test1", "liayiypioyp");
  cout << gfsClient.read("test1") << endl; 
}
