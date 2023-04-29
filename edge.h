#ifndef EDGE
#define EDGE

#include <string>

class Edge {
    public:
        int weight;             // the distance covered by the tunnel
        bool alreadyExists;     // whether or not the connection already exists between the source and destination
        int boresUnder;         // how many buildings the tunnel would go under if made

        Edge() {
            weight = 9999;
            alreadyExists = false;
            boresUnder = 0;
        }
        
        Edge(int w, bool ae, int bu ) {
            weight = w;
            alreadyExists = ae;
            boresUnder = bu;
        }

        void operator=(const Edge& other) {
            weight = other.weight;
            alreadyExists = other.alreadyExists;
            boresUnder = other.boresUnder;
        }
};

#endif