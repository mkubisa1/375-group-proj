#include "edge.h"
#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <stack>

std::vector<Edge> defineGraph() {
    // In the graph implementation, nodes are implicitly represented by vector indeces. A node in turn represents a building on campus as defined in the spreadsheet.
    // The graph is stored as a two-dimesional array of Edges. A tunnel connecting two buildings is represented by an edge at graph[i][j], where i and j are the buildings on either end.
    // The graph is indexed by row, then column. For example, the tunnel connecting AA-CW-LH to S2-SL is stored in graph[0][2], and the weight of the edge stored there is 220.

    // buildings from spreadsheet to vector indeces are defined as such:
    // AA-CW-LH    = 0     LN-LS-LT-TH = 4     AM = 8          WH-OH = 12
    // AB-S1       = 1     FA-AC       = 5     AD = 9
    // S2-SL       = 2     EB          = 6     OR-OD = 10
    // S3-S4-S5    = 3     UU-UUW      = 7     OO-OJ = 11

    std::vector<Edge> output;

    output.push_back(Edge(0,1,70,0,true));
    output.push_back(Edge(0,2,220,1));
    output.push_back(Edge(0,3,554,2));
    output.push_back(Edge(0,4,219,0));
    output.push_back(Edge(0,5,567,0));
    output.push_back(Edge(0,6,621,1));
    output.push_back(Edge(0,7,741,1));
    output.push_back(Edge(0,8,1233,2));
    output.push_back(Edge(0,9,1167,2));
    output.push_back(Edge(0,10,1413,2));
    output.push_back(Edge(0,11,1388,2));
    output.push_back(Edge(0,12,1772,2));

    output.push_back(Edge(1,2,51,0));
    output.push_back(Edge(1,3,336,1));
    output.push_back(Edge(1,4,191,0));
    output.push_back(Edge(1,5,346,0));
    output.push_back(Edge(1,6,693,1));
    output.push_back(Edge(1,7,721,0));
    output.push_back(Edge(1,8,1244,2));
    output.push_back(Edge(1,9,910,1));
    output.push_back(Edge(1,10,1237,1));
    output.push_back(Edge(1,11,1314,1));
    output.push_back(Edge(1,12,1697,1));
    
    output.push_back(Edge(2,3,83,0));
    output.push_back(Edge(2,4,471,0));
    output.push_back(Edge(2,5,266,0));
    output.push_back(Edge(2,6,836,0));
    output.push_back(Edge(2,7,726,1));
    output.push_back(Edge(2,8,1252,2));
    output.push_back(Edge(2,9,844,1));
    output.push_back(Edge(2,10,1198,1));
    output.push_back(Edge(2,11,1321,2));
    output.push_back(Edge(2,12,1623,2));

    output.push_back(Edge(3,4,679,1));
    output.push_back(Edge(3,5,238,0));
    output.push_back(Edge(3,6,996,1));
    output.push_back(Edge(3,7,929,1));
    output.push_back(Edge(3,8,1332,2));
    output.push_back(Edge(3,9,852,1));
    output.push_back(Edge(3,10,1198,1));
    output.push_back(Edge(3,11,1384,1));
    output.push_back(Edge(3,12,1666,2));

    output.push_back(Edge(4,5,193,0));
    output.push_back(Edge(4,6,101,0,true));
    output.push_back(Edge(4,7,234,0));
    output.push_back(Edge(4,8,760,2));
    output.push_back(Edge(4,9,708,1));
    output.push_back(Edge(4,10,945,0));
    output.push_back(Edge(4,11,905,2));
    output.push_back(Edge(4,12,1318,2));

    output.push_back(Edge(5,6,390,0));
    output.push_back(Edge(5,7,148,0));
    output.push_back(Edge(5,8,570,0));
    output.push_back(Edge(5,9,200,0));
    output.push_back(Edge(5,10,552,0));
    output.push_back(Edge(5,11,642,1));
    output.push_back(Edge(5,12,961,0));

    output.push_back(Edge(6,7,92,0));
    output.push_back(Edge(6,8,429,1));
    output.push_back(Edge(6,9,739,1));
    output.push_back(Edge(6,10,836,1));
    output.push_back(Edge(6,11,588,1));
    output.push_back(Edge(6,12,1025,2));

    output.push_back(Edge(7,8,104,0));
    output.push_back(Edge(7,9,416,0));
    output.push_back(Edge(7,10,366,0));
    output.push_back(Edge(7,11,229,0));
    output.push_back(Edge(7,12,618,0));

    output.push_back(Edge(8,9,577,0));
    output.push_back(Edge(8,10,340,0));
    output.push_back(Edge(8,11,71,0));
    output.push_back(Edge(8,12,469,1));

    output.push_back(Edge(9,10,229,0));
    output.push_back(Edge(9,11,560,0));
    output.push_back(Edge(9,12,685,1));

    output.push_back(Edge(10,11,213,0));
    output.push_back(Edge(10,12,127,0));

    output.push_back(Edge(11,12,134,0));

    std::sort(output.begin(), output.end(), compareEdges);  // sort the edges by length

    return output;
}


std::vector<Edge> prim(std::vector<Edge> input) {
    bool visited[13]; for(int i = 0; i < 13; i++) {visited[i] = false;}   // array to keep track of visited nodes
    std::vector<Edge> mst;

    std::priority_queue<Edge> pq;    //use a priority queue to store edges to check; sorted by weight

    // start with node 0
    visited[0] = true;
    for(int i = 0; i < input.size(); i++) {
        if((input.at(i).src == 0) || (input.at(i).dst == 0)) { pq.push(input.at(i)); }   // if edge involves node 0, add it to queue
    }

    while(!pq.empty()) {
    Edge e = pq.top();
    pq.pop();
    if(visited[e.dst] && visited[e.src]) { continue; }

    int next_node;
    if (!visited[e.dst]) {
        visited[e.dst] = true;
        next_node = e.dst;
    } else {
        visited[e.src] = true;
        next_node = e.src;
    }
    mst.push_back(e);

    for(int i = 0; i < input.size(); i++) {
        if((input.at(i).src == next_node) || (input.at(i).dst == next_node)) {
            if ((!visited[input.at(i).src] || !visited[input.at(i).dst])) {
                pq.push(input.at(i));
            }
        }
    }
}
    return mst;
}


int find(std::vector<int> &parent, int i) {
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

void Union(std::vector<int> &parent, int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);
    parent[xroot] = yroot;
}

std::vector<Edge> kruskal(std::vector<Edge> &edges) {
    std::vector<Edge> mst;
    int e = 0; 
    int i = 0; 
    int V = 13;
    std::sort(edges.begin(), edges.end(), compareEdges);

    std::vector<int> parent(V);
    for (int v = 0; v < V; ++v)
        parent[v] = v;

    while (e < V - 1 && i < edges.size()) {
        Edge next_edge = edges[i++];

        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dst);

        if (x != y) {
            mst.push_back(next_edge);
            Union(parent, x, y);
            e++;
        }
    }
    return mst;
}

int main() {

    std::vector<Edge> baseGraph = defineGraph();

    // run and show prim algorithm
    std::vector<Edge> primMST = prim(baseGraph);
    std::cout << "Prim result:" << std::endl;
    for(int i = 0; i < primMST.size(); i++) { primMST.at(i).show();}

    std::vector<Edge> kruskalMST = kruskal(baseGraph);
    std::cout << std::endl << std::endl << std::endl;
    std::cout << "Kruzkal result:" << std::endl;
    for(int i = 0; i < kruskalMST.size(); i++) { kruskalMST.at(i).show();}
    
    return 0;
}