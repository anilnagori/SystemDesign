/*

1.Consistent Hashing

A general database method for performing a horizontal shard is to take the id against the total number of database servers n 
and then to find out which machine it is on. The disadvantage of this method is that as the data continues to increase, we need 
to increase the database server. When n is changed to n+1, almost all the data has to be moved, which causes no consistency. In 
order to reduce the defects caused by this naive hash method (%n), a new hash algorithm emerges: Consistent Hashing, Consistent 
Hashing. There are many ways to implement this algorithm. Here we implement a simple Consistent Hashing.

The id is modeled on 360. If there are 3 machines at the beginning, then the 3 machines are responsible for the three parts of 
0~119, 120~239, 240~359. Then, how much is the model, check which zone you are in, and which machine to go to.
When the machine changes from n to n+1, we find the largest one from the n intervals, then divide it into two and give half to 
the n+1th machine.
For example, when changing from 3 to 4, we find the third interval 0~119 is the current largest interval, then we divide 0~119 
into 0~59 and 60~119. 0~59 is still given to the first machine, 60~119 to the fourth machine.
Then we changed from 4 to 5, and we found that the largest interval is the third interval 120~239. After dividing into two, it 
becomes 120~179, 180~239.
Suppose all the data is on one machine at the beginning. When adding to the nth machine, what is the distribution of the interval 
and the corresponding machine number?

Notice:
You can assume n <= 360. At the same time, we agree that when there are multiple occurrences in the maximum interval, we split the 
machine with the smaller number.
For example, the size of 0~119, 120~239 is 120, but the number of the previous machine is 1, and the number of the latter machine 
is 2, so we split the range of 0~119.

Clarification:
If the maximal interval is [x, y], and it belongs to machine id z, when you add a new machine with id n, you should divide [x, y, z]
into two intervals: [x, (x + y) / 2, z] and [(x + y) / 2 + 1, y, n]

Example
for n = 1, return
[
  [0,359,1]
]
represent 0~359 belongs to machine 1.

for n = 2, return
[
  [0,179,1],
  [180,359,2]
]

for n = 3, return
[
  [0,89,1]
  [90,179,3],
  [180,359,2]
]

for n = 4, return
[
  [0,89,1],
  [90,179,3],
  [180,269,2],
  [270,359,4]
]

for n = 5, return
[
  [0,44,1],
  [45,89,5],
  [90,179,3],
  [180,269,2],
  [270,359,4]

*/
