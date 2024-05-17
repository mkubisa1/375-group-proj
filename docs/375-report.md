# CS 375 Project: Connecting the Brain
**Benjamin Fox; Matthew Kubisa**

Below are the contents of the formal report submitted alongside our project.

## Problem Statement

### Context
Some buildings on campus are physically connected to each other, such that one does not need to go outside in order to travel between them. This kind of connection has multiple benefits, including:
* Being able to avoid going outside in bad weather (rain, cold, snow, etc)
* Safer movement between buildings at night

### Problem Statement
Assume that Binghamton University would like to expand interior traversal between buildings by connecting them with tunnels. To save on construction time and costs, the school would like to know the most efficient routes on which to dig tunnels.

To address this problem, our objective is to algorithmically construct a minimum spanning tree on a graph representing the university's main campus, with nodes representing destinations and edges representing tunnels. We have chosen to narrow the scope of the problem to only include buildings located within the campus's main loop (which is sometimes referred to as "The Brain").

## Considerations

### Pre-Existing Connections
As mentioned in *Context*, some buildings on the main campus already allow for interior movement between them, because they are architecturally connected. To account for this, groups of buildings which exhibit this quality are consolidated into single nodes in our graph. For example: the Lecture Hall, Classroom Wing, and Academic Building A are all connected physically, so they are combined into a single node which represents the whole cluster.

In addition, a few buildings (or building groups) already have passageways between them, even if they are not connected architecturally. (For example, Academic buildings A and B have an underground passage between them.) As such, there is no need to construct a new tunnel to connect them. To represent these existing connections, we will still graph edges for them, and assign them a boolean value to denote that they already exist. Pre-existing connections are to be present in the final minimum spanning tree.

### Construction Cost
Each edge in our data structure contains properties for length, number of buildings bored under, and whether or not the connection already exists, as well as the final weight calculation. In general, we devised two factors in boring a given tunnel which would affect construction cost:

1. The length of the tunnel, and
2. If the tunnel is to be dug underneath any existing buildings, which is assumed to be more dangerous and time-consuming than digging through soil only.

To account for these factors, our graph is weighted, with edge weights calculated through an equation:

`weight = [length + (length * buildingsBoredUnder)] * !(alreadyExists)`

Where `length` and `buildingsBoredUnder` are positive integers, and `alreadyExists` is a boolean value interpreted as either 0 for "false", or 1 for "true." `alreadyExists` is a binary value that is flipped in the weight calculation, as denoted by the `!()` notation. In effect, if `alreadyExists` for an edge is "true", the equation would set the weight to 0 to ensure its inclusion in the final MST.

## Algorithm
On a surface level, our procedure for addressing the stated problem is as follows:

1. Input a connected, weighted and undirected graph representing the main campus, with nodes representing building groups and edges representing possible tunnels to be bored.
2. Use both Prim's and Kruskal's algorithm to find the minimum spanning tree of the input graph.
3. Return the minimum spanning tree to the end user.

The graph is stored in our program as an adjacency matrix represented by a vector of Edges. `Edge` is a custom class created for our program; each edge has properties storing length (int), number of buildings bored under (int), whether the connection already exists (boolean), and the calculated edge weight (int).

### Using Both Prim's and Kruskal's Algorithms
To expand the scope of our project, we chose to implement both Prim and Kruskal's algorithms to find the minimum spanning tree. In theory, they should provide similar if not identical results. In the context of our problem, the University may want to do this in practice to ensure the results found are correct. Implementing both algorithms allows each one to "check" the other's result and raise confidence in the final answer.

### Initial Graph Construction
While our program finds the minimum spanning tree on its own, the fully connected graph provided as input was constructed manually. First, it was determined how the buildings should be consolidated into nodes based on existing connections using satellite imagery of the campus; we came up with 13 nodes to cover all buildings.

Next, the lengths for each edge was found using the "measure distance" feature in Google Maps, which allows the user to estimate the distance between any two points on the map. To minimize bias in the final result, the endpoints for each measurement were placed on the walls of the two buildings closest to each other. All length values are recorded in feet.

If a connection we made went through any other existing buildings, the number of buildings it went through was also recorded into the edge's "buildingsBoredUnder" property as discussed in Construction Cost.

### Case Analysis for Kruskal's Algorithm
*This section satisfies the project requirement to analyze a different case analysis for Kruskal's algorithm, due to it already being implemented in a previous assignment.*

The version of Kruskal's algorithm implemented in class used the find-union (disjoint subset) implementation. As the input graph was complete and therefore dense, its time complexity was O(V^2*log(V)).

For our project, the algorithm's implementation is roughly as follows:
1. Create a disjoint set for each vertex of the graph.
2. Sort all the edges of the graph in non-decreasing order according to the weight calculation above.
3. For each edge in the sorted list:
    * Check if the vertices of the edge belong to different disjoint sets. If they do, it means that adding this edge to the minimum spanning tree will not create a cycle. Therefore, we can safely add the edge and merge the two sets.
    * If the vertices of the edge belong to the same disjoint set, it means that adding this edge to the minimum spanning tree will create a cycle. So we then discard the edge.
4. Repeat step 3 until all the edges have been processed.

This was done using weights in the undirected, complete graph which were non-negative. The weight is a factor of price and time, both of which are non-negative.

#### Negative Edge Weights
If we were to also allow negative edge weights, the output MST would remain the same. Kruskal's algorithm can handle negative weights while still producing the optimal result; this is because proof of correctness doesn't rely on edge weights being positive. When sorted, the negative weights would appear before the positive ones in the list of edges, so the above procedure would not change and the algorithm would still yield an MST.

#### Directed Graph
The input graph on which Kruskal's algorithm operates is undirected, as pedestrians can pass both ways from within a tunnel. If we needed to instead use a directed input graph, our implementation of the algorithm would fail. For example: if we have edges formatted as (source, node), then the list of edges {(3,7),(7,4),(3,4)} would be reported as having a cycle in the find-union method, but it is trivial to see that the actual graph will not contain one (in the directed version).

In a real-world scenario, a directed graph may be needed if the tunnels were intended for non-pedestrian use, such as if they contained a one-way rail system.

#### Disconnected Graph

In the special case that the graph is not connected, Kruskal's algorithm would still work. However, instead of creating a minimum spanning tree, it would create a minimum spanning forest. This use case might be useful if we were to also try connecting more distant destinations with our tunnel system, such as the Pharmacy School or Downtown Center. (Ignoring the fact these distances may be too far for someone to walk in practice.) Kruskal's algorithm would still yield the MSTs at each individual location, assuming we take the same approach as the current implementation using connected graphs.

## Results
Using both Prim's and Kruskal's algorithms (they each provide the same result), our program created the minimum spanning tree shown below:

[Results graph](./375-result-graph.jpg)

The nodes correlate with building groups as such:

0. Academic A / Classroom Wing / Lecture Hall 
1. Academic B / Science 1
2. Science 2 / Science Library
3. Science 3 / Science 4 / Science 5
4. Library North / Library South / Library Tower / Technology Hub
5. Fine Arts / Anderson Center
6. Engineering Building
7. University Union / University Union West
8. Couper Administration Building
9. Admissions Center
10. Old Rafuse / Old Digman
11. Old O'Connor / Old Johnson
12. Whitney Hall / Old Champlain

Note that, for illustrative purposes, the locations of the nodes in the pictured graph do not correlate with the relative locations of the building groups they represent.

Edges with 0 weight represent connections which already exist.

None of the tunnels in the output MST would bore under any buildings.

## Potential Improvements
If our program or a similar one was needed in a real-world scenario, it may be wise to consider some additional factors:

* All potential tunnels are defined as straight lines. In reality, a tunnel could be curved, such as to go around buildings. This would increase length but could also eliminate the need to dig under buildings.
* Although it was not tested for, it's possible that intersections exist between two or more tunnels in the input graph. This doesn't affect the validity of the final solution, but one could take advantage of this to reduce complexity (ex. building an underground "hub" at which several tunnels converge).
* Elevation, and costs associated with digging at or between different elevations, was not considered.
* The specific costs associated with digging into different types of soil or rock were not considered; only the assumption that digging under buildings is less desirable than digging only through soil.
