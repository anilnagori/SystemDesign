/*

3.Friendship Service

Support follow & unfollow, getFollowers, getFollowings.

Example:
follow(1, 3)
getFollowers(1) // return [3]
getFollowings(3) // return [1]
follow(2, 3)
getFollowings(3) // return [1,2]
unfollow(1, 3)
getFollowings(3) // return [2]

*/

#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <cassert>

using namespace std;

class  FriendshipService {
public:
    FriendshipService () { }

    // @param userId an integer
    // return all followers and sort by userId
    vector<int> getFollowers(int userId) {
        if (graph.count(userId) == 0) {
          return { };
        }

        set<int>& followerSet = graph[userId].first;
        
        return vector<int> (followerSet.begin(), followerSet.end());
    }
        
    // @param userId an integer
    // return all followings and sort by userId
    vector<int> getFollowings(int userId) {
        if (graph.count(userId) == 0) {
          return { };
        }

        set<int>& followeeSet = graph[userId].second;
        
        return vector<int> (followeeSet.begin(), followeeSet.end());
    }

    // @param fromUserId, an integer
    // @param to_user_id an integer
    // fromUserId follows toUserId
    void follow(int fromUserId, int toUserId) {
        graph[fromUserId].first.insert(toUserId);
        graph[toUserId].second.insert(toUserId);
    }

    // @param fromUserId, an integer
    // @param to_user_id an integer
    // fromUserId unfollows toUserId
    void unfollow(int fromUserId, int toUserId) {
        if (graph.count(fromUserId) == 0 || graph.count(toUserId)) {
          return;
        }

        graph[fromUserId].first.erase(toUserId);
        graph[toUserId].second.erase(toUserId);
    }

private:
    // key - user, value - followers, followees
		unordered_map<int, pair<set<int>, set<int>>> graph;
};

int main() {
  FriendshipService friendshipService;

  friendshipService.follow(1, 3);
  friendshipService.follow(3, 5);

  auto followers = friendshipService.getFollowers(3);

  copy(followers.begin(), followers.end(), ostream_iterator<int>(cout, ", "));
  cout << endl;

  auto followees = friendshipService.getFollowings(3);

  copy(followees.begin(), followees.end(), ostream_iterator<int>(cout, ", "));
  cout << endl;
}
