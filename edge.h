#ifndef EDGE
#define EDGE
#include <iostream>

class Edge {
    public:
        int src, dst;           // the nodes on the two ends of the edge
        int length;             // the length of the tunnel
        bool alreadyExists;     // whether or not the connection already exists
        int boresUnder;         // how many buildings the tunnel was listes as going under

        Edge(int s, int d, int l, int bu, bool ae) {
            src = s;
            dst = d;
            length = l;
            boresUnder = bu;
            alreadyExists = ae;

            // incorporate boresUnder into the length property, to effectively make it a measure of how difficult it would be to make the tunnel
            length = length + (length*boresUnder);
        }

        Edge(int s, int d, int l, int bu) { // if no bool for alreadyExists is given, assume it is false.
            src = s;
            dst = d;
            length = l;
            boresUnder = bu;
            alreadyExists = false;

            // incorporate boresUnder into the length property, to effectively make it a measure of how difficult it would be to make the tunnel
            length = length + (length*boresUnder);
        }
        
        void show() { std::cout << "connects " << src << " and " << dst << "; length = " << length << "; bores under " << boresUnder << " buildings" << std::endl; }

        bool operator<(const Edge& other) const { return this->length > other.length; }
};

bool compareEdges(const Edge& e1, const Edge& e2) { return e1.length < e2.length; } // used for sorting by length

#endif