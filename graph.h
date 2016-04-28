#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>

template <class NODEKEY>
class Edge{
public:
    Edge(const NODEKEY &k)
    {
        key = k;
        nextedge = nullptr;
    }
    NODEKEY key;
    Edge *nextedge;
};

/////////////////////////////////////////////////////////

template <class NODEKEY, class NODEDATA>
class Vertex{
public:
    Vertex(const NODEKEY &k, const NODEDATA &d)
    {
        key = k;
        data = d;
        nextedge = nullptr;
        nextvertex = nullptr;
    }
    NODEKEY key;
    NODEDATA data;
    Vertex *nextvertex;
    Edge<NODEKEY> *nextedge;
};

/////////////////////////////////////////////////////////

template <class NODEKEY, class NODEDATA>
class Graph{
public:
    Graph();
    void insertVertex(const NODEKEY &, const NODEDATA &);
    void insertEdge(const NODEKEY &, const NODEKEY &);
    void printVertex() const;
    void printEdge(const NODEKEY &) const;
private:
    Vertex<NODEKEY, NODEDATA> *rootptr;
    int graphsize;

    void insertVertexHelper(Vertex<NODEKEY, NODEDATA> **, const NODEKEY &, const NODEDATA &);
    bool isVertex(const Vertex<NODEKEY, NODEDATA> *, const NODEKEY &);
    void insertEdgeHelper(Edge<NODEKEY> **, const NODEKEY &);
};


template <class NODEKEY, class NODEDATA>
Graph<NODEKEY, NODEDATA>::Graph() { rootptr = nullptr; graphsize = 0; }

template <class NODEKEY, class NODEDATA>
void Graph<NODEKEY, NODEDATA>::insertVertex(const NODEKEY &key, const NODEDATA &data)
{
    insertVertexHelper(&rootptr, key, data);
}

template <class NODEKEY, class NODEDATA>
void Graph<NODEKEY, NODEDATA>::insertVertexHelper(Vertex<NODEKEY, NODEDATA> **ptr, const NODEKEY &key, const NODEDATA &data)
{
    if (*ptr == nullptr)
        *ptr = new Vertex<NODEKEY, NODEDATA> (key, data);
    else
        insertVertexHelper( &((*ptr)->nextvertex), key, data);
    graphsize++;
}

template <class NODEKEY, class NODEDATA>
void Graph<NODEKEY, NODEDATA>::printVertex() const
{
    auto ptr = rootptr;
    while(ptr != nullptr)
    {
         std::cout << ptr->key << "\n";
         ptr = ptr->nextvertex;
    }
}

template <class NODEKEY, class NODEDATA>
void Graph<NODEKEY, NODEDATA>::insertEdge(const NODEKEY &keyfirst, const NODEKEY &keyadd)
{
    if(!isVertex(rootptr, keyfirst))
    {
        std::cout << "Error: vertex 1 not found\n";
        return;
    }
    if(!isVertex(rootptr, keyadd))
    {
        std::cout << "Error: vertex 2 not found\n";
        return;
    }

    auto vertexptr = rootptr;
    while(vertexptr->key != keyfirst)
    {
        vertexptr = vertexptr->nextvertex;
    }

    insertEdgeHelper(&(vertexptr->nextedge), keyadd);
    std::cout << "Edge " << keyfirst << " to " << keyadd << " add\n";
}

template <class NODEKEY, class NODEDATA>
void Graph<NODEKEY, NODEDATA>::insertEdgeHelper(Edge<NODEKEY> **edgeptr, const NODEKEY &key)
{
    if (*edgeptr == nullptr)
        *edgeptr = new Edge<NODEKEY> (key);
    else
        insertEdgeHelper(&((*edgeptr)->nextedge), key);
}

template <class NODEKEY, class NODEDATA>
bool Graph<NODEKEY, NODEDATA>::isVertex(const Vertex<NODEKEY, NODEDATA> *ptr, const NODEKEY &key)
{
    if (ptr == nullptr)
        return false;
    if (ptr->key == key)
        return true;
    else
        return isVertex(ptr->nextvertex, key);
}

template <class NODEKEY, class NODEDATA>
void Graph<NODEKEY, NODEDATA>::printEdge(const NODEKEY &key) const
{
    auto vertexptr = rootptr;
    while(vertexptr->key != key)
    {
        vertexptr = vertexptr->nextvertex;
        if (vertexptr == nullptr)
        {
            std::cout << "vertex " << key << " not found\n";
            return;
        }
    }
    auto edgeptr = vertexptr->nextedge;
    std::cout << "vertex " << key << " edge: ";
    while(edgeptr != nullptr)
    {
        std::cout << edgeptr->key << " | ";
        edgeptr = edgeptr->nextedge;
    }
     std::cout << "\n";
}

#endif // GRAPH_H
