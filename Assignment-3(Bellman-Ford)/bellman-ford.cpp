#include <bits/stdc++.h>
#include <ctime>
using namespace std;

struct Edge
{
    //vertices are represented as Integers
    int sourceVertex, destinationVertex, weight;
};


/*
This function prints the minimum distance of all vertices from source vertex
Or notifies if there exists a negative weight cycle
Number of vertices(V), number of edges(E), source vertex(src) and list of Edges are passed as arguments
*/
void BellmanFord(int V, int E, int src, Edge edgeList[]){
    int distanceFromSrc[V];

    //Initialize all distances to INT_MAX and source to zero
    for (int i = 0; i < V; i++)
        distanceFromSrc[i]   = INT_MAX;
    distanceFromSrc[src] = 0;

    //run the bellman-ford algorithm
    for (int i = 1; i <= V-1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = edgeList[j].sourceVertex;
            int v = edgeList[j].destinationVertex;
            int weight = edgeList[j].weight;
            if (distanceFromSrc[u] != INT_MAX && distanceFromSrc[u] + weight < distanceFromSrc[v])
                distanceFromSrc[v] = distanceFromSrc[u] + weight;
        }
    }

    //flag to indicate if there exists a negative weight cycle or not
    bool flag = false;

    //Check for negative weight cycle
    for (int i = 0; i < E; i++)
    {
        int u = edgeList[i].sourceVertex;
        int v = edgeList[i].destinationVertex;
        int weight = edgeList[i].weight;
        if (distanceFromSrc[u] != INT_MAX && distanceFromSrc[u] + weight < distanceFromSrc[v])
            flag = true;
    }

    //If there exists a negative weight cycle then notify the user
    if(flag){
        cout<<"Graph contains negative weight cycle"<<endl;
    }
    //Else print the minimum distances of all vertices from source vertex
    else {
        cout<<"Vertex Distances from Source vertex=" << src <<" are : "<<endl;
        for (int i = 0; i < V; ++i)
            cout<<"Vertex =" << i <<"  , distance = "<< distanceFromSrc[i] <<endl;
    }

}

int main(){
    int V,E;
    cin>> V >> E;
    Edge edges[E];
    for(int i=0; i<E; i++)
        cin>> edges[i].sourceVertex >> edges[i].destinationVertex >> edges[i].weight;

	clock_t tStart = clock();

	BellmanFord(V, E, 0, edges);

	printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
