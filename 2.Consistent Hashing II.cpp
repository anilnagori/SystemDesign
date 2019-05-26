/*

2.Consistent Hashing II

In Consistent Hashing I we introduced a relatively simple consistency hashing algorithm. This simple version 
has two drawbacks:
- After adding a machine, the data comes from one of the machines. The read load of this machine is too large, 
  which will affect the normal service.
- When added to 3 machines, the load of each server is not balanced, it is 1:1:2.

To solve this problem, the concept of micro-shards was introduced. A better algorithm is this:

Divide the 360° interval to be finer. Change from 0~359 to a range of 0~n-1, and connect the sections end to 
end, and connect them into a circle. When joining a new machine, randomly choose to sprinkle k points in the 
circle, representing the k micro-shards of the machine.

Each data also corresponds to a point on the circumference, which is calculated by a hash function.

A data belongs to the machine that is responsible for management, and is determined by the machine to which the 
first micro-shard point touched clockwise on the circle corresponding to the point on the circumference of the 
data. n and k are typically 2^64 and 1000 in a real NoSQL database.

Implement this method that introduces a micro-shard's consistent hashing. The main implementation of the following 
three functions:

create(int n, int k)
addMachine(int machine_id) // add a new machine, return a list of shard ids.
getMachineIdByHashCode(int hashcode) // return machine id

Notice:
When n is 2^64, there is basically no repetition in the interval within this interval.
But to make it easier to test the correctness of your program, n may be smaller in the data, so you must ensure 
that the k random numbers you generate do not duplicate.
LintCode does not judge the correctness of your returnMachine's return (because it is a random number), it will 
only judge the correctness of your getMachineIdByHashCode result based on the result of the addMachine you return.

Example:
create(100, 3)
addMachine(1)
>> [3, 41, 90] => Three random numbers
getMachineIdByHashCode(4)
>> 1
addMachine(2)
>> [11, 55, 83]
getMachineIdByHashCode(61)
>> 2
getMachineIdByHashCode(91)
>> 1
*/

