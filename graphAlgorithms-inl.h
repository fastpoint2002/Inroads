/*
  Inroads
*/

#include <stdexcept>
#include "adts/stlQueue.h"
#include "adts/stlMinPriorityQueue.h"
#include "adts/dictionary.h"
#include "adts/stlStack.h"

template <typename V, typename E, typename W>
bool reachableDFS(V src, V dest, Graph<V, E, W>* g) {
    // initialize variables
    STLStack<V> exploration;
    STLHashTable<V,V> previous;
    vector<V> neighbors;
    V current, cneighbor, temp;
    int nsize, psize, i;

    exploration.push(src);
    previous.insert(src, src);

    while(!(exploration.isEmpty())) {
        current = exploration.pop();
        
        if (current == dest) {
            return true;
        }

        neighbors = g->getNeighbors(current);
        nsize = neighbors.size();

        for(i=0; i<nsize; i++) {
            cneighbor = neighbors[i];
            if (!(previous.contains(cneighbor))) {
                previous.insert(cneighbor, current);
                exploration.push(cneighbor);
            }
        }
    }
    return false;
}

template <typename V, typename E, typename W>
vector<V> shortestLengthPathBFS(V src, V dest, Graph<V, E, W>* g) {
    // initialize variables
    STLQueue<V> exploration;
    STLHashTable<V,V> previous;
    vector<V> neighbors;
    V current, cneighbor, temp;
    int nsize, psize, i;

    exploration.enqueue(src);
    previous.insert(src, src);

    while(!(exploration.isEmpty())) {
        current = exploration.dequeue();
        
        if (current == dest) {
            vector<V> path;
            while (current != src) {
                path.push_back(current);
                current = previous.get(current);
            }
            path.push_back(src);
            psize = path.size();
            
            vector<V> rpath;
            for (i = 0; i < psize; i++) {
                rpath.push_back(path[(psize-i-1)]);
            }
            return rpath;
        }

        neighbors = g->getNeighbors(current);
        nsize = neighbors.size();

        for(i=0; i<nsize; i++) {
            cneighbor = neighbors[i];
            if (!(previous.contains(cneighbor))) {
                previous.insert(cneighbor, current);
                exploration.enqueue(cneighbor);
            }
        }
    }
    throw runtime_error("No path found in shortestLengthPathBFS");
}

template <typename V, typename E, typename W>
Dictionary<V, W>* singleSourceShortestPath(V src, Graph<V, E, W>* g) {
    // initialize variables
    STLMinPriorityQueue<W,V> exploration;
    STLHashTable<V,W>* costs = new STLHashTable<V,W>();
    vector<Edge<V, E, W>> edges;
    V current, cneighbor, temp;
    int nsize, psize, i;
    W currentcost, newcost;

    exploration.insert(0, src);
    costs->insert(src, 0);

    while(!(exploration.isEmpty())) {
        current = exploration.remove();
        currentcost = costs->get(current);

        edges = g->getOutgoingEdges(current);
        nsize = edges.size();

        for(i=0; i<nsize; i++) {
            cneighbor = edges[i].getDestination();
            newcost = currentcost + edges[i].getWeight();

            if (!(costs->contains(cneighbor))) {
                costs->insert(cneighbor, newcost);
                exploration.insert(newcost, cneighbor);
            }
            else if (costs->get(cneighbor)>newcost) {
                costs->update(cneighbor, newcost);
                exploration.insert(newcost, cneighbor);
            }
        }
    }
    return costs;
}
