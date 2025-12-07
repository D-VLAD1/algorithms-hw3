# algorithms-hw3

### Variant 2

#### The work is done by Vladyslav Danylyshyn

The task was to join pairs without given nodes(I call them as forbidden nodes).

Let's dive in the program's flow. First of all, the program has specific input 
requirement. It looks like:

```
8 -> nodes amount
3 6 -> forbidden nodes
11 -> amount of edges
1 2 |
2 3 |-> edges
2 4 |
...
```

So, when one runs the program, one should write that type of input.

Then program processes given input and calls `connect(...)` function.
The function takes nodes amount, vector with booleans(if the node is forbidden or not)
and all the edges.

`connect(...)` function initializes S and T nodes for our maxflow algorithm and creates
vector of `node_t` class instances. Then, we create adjacency list without forbidden nodes in order to split nodes
into U and V groups using graph painting. After that, we initialize color vector that will keep 
color of our nodes. By default, the vector carries -1 values(U group will be 0, V --> 1). 
Then, we run BFS algorithm using adjacency list and paint every node. The first node will be 0, and then
all the others will be `1 - neighboring_painted_node`. The BFS inside for loop, because as we reject forbidden 
nodes, there might be unreachable nodes for our BFS, so we should iterate through not forbidden nodes and give the color.
After painting, we divide nodes to left (U) and right (V) groups. Then we connect those nodes with good edges. And, 
of course, left nodes are connected with S and rights ones with T. We run maxflow (Edmond-Karp) and get how many pairs we have.
Maxflow fills our pairs, so then we can iterate through U group and see pairs of nodes (when capacity of the edge equals weight).
So, we have used edges and amount of pairs, we should return it!

Why have we done painting? If we have 8 nodes and do bipartial graph with 8 nodes on the left side and 8 on
the right side and try to connect them, we can see that nodes could be used twice (if it is
connected on right part, the left part may connect some node as well. It is not what we expect).

## Usage
To run the code, run that:
```shell
mkdir build 
cd build
cmake ..
make
./algorithms_hw3
8
3 6
11
1 2
1 3
2 3
2 4
3 5
4 5
4 6
5 6
6 7
6 8
7 8
```

After running that you will see output. First line - `3`(amount of pairs).\
The other lines - edges in those pairs.

Or another example:
```shell
mkdir build 
cd build
cmake ..
make
./algorithms_hw3
10
4 9
9
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
```

P.S. If output node is not connected with any another node, output will look like `10 -- -1`
