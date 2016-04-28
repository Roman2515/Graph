#include <iostream>
#include <graph.h>
using namespace std;


int main()
{
    Graph<int, int> x;
    x.insertVertex(3, 0);
    x.insertVertex(5, 0);
    x.insertVertex(9, 0);
    x.printVertex();

    x.insertEdge(3, 5);
    x.insertEdge(5, 8);
    x.insertEdge(7, 4);
    x.insertEdge(3, 9);
    x.insertEdge(5, 3);
    x.printEdge(3);
    x.printEdge(4);
    x.printEdge(5);
    return 0;
}
