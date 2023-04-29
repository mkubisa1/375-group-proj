#include "edge.h"
#include <vector>
#include <iostream>
#include <string>

std::vector<std::vector<Edge>> defineGraph() {

    /*
    buildings from spreadsheet to vector indeces are defined as such:
    AA-CW-LH    = 0     LN-LS-LT-TH = 4     AM = 8          WH-OH = 12
    AB-S1       = 1     FA-AC       = 5     AD = 9
    S2-SL       = 2     EB          = 6     OR-OD = 10
    S3-S4-S5    = 3     UU-UUW      = 7     OO-OJ = 11
    */

   std::vector<std::vector<Edge>> output(13);

   Edge test; test.weight = 0; test.alreadyExists = false; test.boresUnder = 0;
   output[0][0] = test;

   return output;

}

int main() {

    std::vector<std::vector<Edge>> graph = defineGraph();

    // std::cout << graph[0][1] << std::endl;

    return 0;
}