#include "edge.h"
#include <vector>
#include <iostream>
#include <string>

std::vector<std::vector<Edge>> defineGraphByEdges() {

    /*
    In the "by edge" graph implementation, nodes are implicitly represented by vector indeces. A node in turn represents a building on campus as defined in the spreadsheet.
    The graph is stored as a two-dimesional array of Edges. A tunnel connecting two buildings is represented by an edge at graph[i][j], where i and j are the buildings on either end.
    The graph is indexed by row, then column. For example, the tunnel connecting AA-CW-LH to S2-SL is stored in graph[0][2], and the weight of the edge stored there is 220.

    buildings from spreadsheet to vector indeces are defined as such:
    AA-CW-LH    = 0     LN-LS-LT-TH = 4     AM = 8          WH-OH = 12
    AB-S1       = 1     FA-AC       = 5     AD = 9
    S2-SL       = 2     EB          = 6     OR-OD = 10
    S3-S4-S5    = 3     UU-UUW      = 7     OO-OJ = 11
    */

   std::vector<std::vector<Edge>> output(13);
   for(int i = 0; i < 13; i++) {
    std::vector<Edge> temp(13);
    output[i] = temp;
   }

    output[0] = { Edge(0,false,0), Edge(70, true, 0), Edge(220,false,1), Edge(554,false,2), Edge(219,false,0), Edge(567,false,0), Edge(621,false,1), Edge(741,false,1), Edge(1233,false,2), Edge(1167,false,2), Edge(1413,false,2), Edge(1388,false,2), Edge(1772,false,2) };
    output[1] = { Edge(), Edge(0,false,0), Edge(51,false,0), Edge(336,false,1), Edge(191,false,0), Edge(346,false,0), Edge(693,false,1), Edge(721,false,0), Edge(1244,false,2), Edge(910,false,1), Edge(1237,false,1), Edge(1314,false,1), Edge(1697,false,1) };
    output[2] = { Edge(), Edge(), Edge(0,false,0), Edge(83,false,0), Edge(471,false,0), Edge(266,false,0), Edge(836,false,0), Edge(726,false,1), Edge(1252,false,2), Edge(844,false,1), Edge(1198,false,1), Edge(1321,false,2), Edge(1623,false,2) };
    output[3] = { Edge(), Edge(), Edge(), Edge(0,false,0), Edge(679,false,1), Edge(238,false,0), Edge(996,false,1), Edge(929,false,1), Edge(1332,false,2), Edge(852,false,1), Edge(1198,false,1), Edge(1384,false,1), Edge(1666,false,2) };
    output[4] = { Edge(), Edge(), Edge(), Edge(), Edge(0,false,0), Edge(193,false,0), Edge(101,true,0), Edge(234,false,0), Edge(760,false,2), Edge(708,false,1), Edge(945,false,0), Edge(905,false,2), Edge(1318,false,2) };
    output[5] = { Edge(), Edge(), Edge(), Edge(), Edge(), Edge(0,false,0), Edge(390,false,0), Edge(148,false,0), Edge(570,false,0), Edge(200,false,0), Edge(552,false,0), Edge(642,false,1), Edge(961,false,0) };
    output[6] = { Edge(), Edge(), Edge(), Edge(), Edge(), Edge(), Edge(0,false,0), Edge(92,false,0), Edge(429,false,1), Edge(739,false,1), Edge(836,false,1), Edge(588,false,1), Edge(1025,false,3) };
    output[7] = { Edge(), Edge(), Edge(), Edge(), Edge(), Edge(), Edge(), Edge(0,false,0), Edge(104,false,0), Edge(416,false,0), Edge(366,false,0), Edge(229,false,0), Edge(618,false,0) };
    output[8] = { Edge(), Edge(), Edge(), Edge(), Edge(), Edge(), Edge(), Edge(), Edge(0,false,0), Edge(577,false,0), Edge(340,false,0), Edge(71,false,0), Edge(469,false,1) };
    output[9] = { Edge(), Edge(), Edge(), Edge(), Edge(), Edge(), Edge(), Edge(), Edge(0,false,0), Edge(229,false,0), Edge(560,false,0), Edge(685,false,1) };
    output[10] = { Edge(), Edge(), Edge(), Edge(), Edge(), Edge(), Edge(), Edge(), Edge(),Edge(), Edge(0,false,0), Edge(213,false,0), Edge(127,false,0) };
    output[11] = { Edge(), Edge(), Edge(), Edge(), Edge(), Edge(), Edge(), Edge(), Edge(), Edge(), Edge(), Edge(0,false,0), Edge(134,false,0) };
    output[12] = { Edge(), Edge(), Edge(), Edge(), Edge(), Edge(), Edge(), Edge(), Edge(), Edge(), Edge(), Edge(), Edge(0,false,0) };

    return output;

    // edge weights deault to 9999 with the default constructor.
    // if you're checking if an edge exists with graph[a][b] and the weight returns 9999,
    // you can then check if graph[b][a] has a value instead
}

std::vector<Edge> prim(std::vector<std::vector<Edge>> graph) {
    
    // init vctor to keep track of visited nodes. indeces line up with those in the graph.
    std::vector<bool> visited(13);
    for(int i = 0; i < 13; i++) { visited.at(i) = false;}

    std::vector<Edge> mst;

    int root = 0;   // define node with index 0 as the starting node

    while(true) {

        std::cout << "iterating prim with root " << root << std::endl;
        
        Edge smallestEdge(9999,false,0);
        int nodeAtSmallestEdge = 9999;

        for(int i = 0; i < 13; i++) {   // for each edge associated with the node we're currently observing (each node has 13 edges associated)

            std::cout << "comparing " << graph[root][i].weight << " < " << smallestEdge.weight << std::endl;

            if(graph[root][i].weight < smallestEdge.weight && graph[root][i].weight > 0) { // if we find an edge with smaller weight

                if(visited[root] == true && visited[i] == true) { continue; }   // skip if both nodes are already visited
                else { 
                    smallestEdge = graph[0][i]; // otherwise, record it as the smallestEdge
                    nodeAtSmallestEdge = i;     // the node at the other end of the edge
                }
            }
        }

        std::cout << "smallest edge weight: " << smallestEdge.weight << std::endl;

        mst.push_back(smallestEdge);                                    // add the smallest edge found to the MST
        visited.at(nodeAtSmallestEdge) = true; visited.at(root) = true; // mark nodes at either end as visited

        //check if all nodes are visited; end infinite loop if so
        for(int i = 0; i < 13; i++) {
            if(visited.at(i) == false) {root = nodeAtSmallestEdge; continue;}           // if any unvisitied nodes are found, repeat loop
            return mst;                                                                 // end infinite loop if no nodes are not yet visited
        }
    }
}

int main() {

    std::vector<std::vector<Edge>> graphByEdges = defineGraphByEdges();
    graphByEdges[1][2].show();

    std::vector<Edge> primMST = prim(graphByEdges);

    return 0;
}