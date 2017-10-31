#include <iostream>
#include "Steiner.h"
#include <fstream>

using namespace std;



int main()
{
    ifstream fin("test1.in");

    SteinerGraph graph(fin);
    graph.AddVirtualLink();
    graph.MST();
    graph.removeVirtualLink();
    graph.removeRedun();
    graph.printTree();

    return 0;
}
