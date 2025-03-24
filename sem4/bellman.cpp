#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <climits>
#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int start;
    int end;
    int weight;
};

struct Map {
    vector<int> nodes;
    vector<Edge> edges;
};
struct Path {
    int distance;
    bool negativeCycle;
    bool unreachable;
};

Path bellman_ford(Map &map, int source, int target, vector<int> &parent) {
    int V = map.nodes.size();
    int E = map.edges.size();
    
    vector<int> distance(V, INT_MAX);
    distance[source] = 0;  
    parent[source] = -1;  

    for(int i = 0; i < V - 1; i++) {
        for(int j = 0; j < E; j++) {
            int u = map.edges[j].start;
            int v = map.edges[j].end;
            int weight = map.edges[j].weight;
            if(distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
            }
        }
    }

    for(int j = 0; j < E; j++) {
        int u = map.edges[j].start;
        int v = map.edges[j].end;
        int weight = map.edges[j].weight;
        if(distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
            return {-1, true, false}; // Negative cycle detected
        }
    }

    if(distance[target] == INT_MAX) {
        return {-1, false, true}; // Unreachable
    }

    return {distance[target], false, false}; // Valid shortest path
}


void print_path(vector<int> &parent, int target) {
    vector<int> path;
    for(int v = target; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    for(size_t i = 0; i < path.size(); i++) {
        cout << path[i] <<(i + 1 == path.size() ? "\n" : " -> ");
    }
}

void init(Map &map, const string &filename) {
    ifstream file(filename);
    if(!file) {
        cerr << "Error opening file: " << filename << "\n";
        return;
    }

    int numEdges;
    file >> numEdges;

    map.edges.resize(numEdges);

    for(int i = 0; i < numEdges; i++) {
        file >> map.edges[i].start >> map.edges[i].end >> map.edges[i].weight;
    }

    file.close();
}

int main() {
    Map map;
    int V = 8; 
    for(int i = 0; i < V; i++) {
        map.nodes.push_back(i);
    }

    init(map, "edges.txt");

    int source = 0; 
    int target = 7; 
    Path result;
    vector<int> parent(V, -1);


    for(int i = 0; i < 7; i++) {
        result = bellman_ford(map, i, target, parent);
    
        if(result.negativeCycle) {
            cout << "Negative cycle detected.\n";
        } 
        else if(result.unreachable) {
            cout << "Target is unreachable from node " << i << ".\n\n";
        }
        else {
            print_path(parent, target);
            cout << "Distance: " << result.distance << "\n\n";
        }
    }
    


    return 0;
}
