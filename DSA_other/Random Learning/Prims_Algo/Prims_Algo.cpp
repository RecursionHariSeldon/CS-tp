#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct edge {
    char from;
    char to;
    int weight;
};

edge create_edge(char a, char b, int weight) {
    edge example;
    example.from = a;
    example.to = b;
    example.weight = weight;

    return example;
}

vector<edge> create_graph(vector<char> v1, vector<char> v2, vector<int> weights) {
    int no_of_edges = v1.size();
    vector<edge> graph;
    for (int i = 0; i < no_of_edges; i++) {
        graph.push_back(create_edge(v1[i], v2[i], weights[i]));
        graph.push_back(create_edge(v2[i], v1[i], weights[i]));
    }

    return graph;
}

void print_graph(vector<edge> graph) {
    for (edge i : graph) {
        cout << i.from << "  --  " << i.weight << "  --  " << i.to<< endl;
    }
}

int num_vertices(vector<edge> graph) {
    vector<char> vertices = {};
    for (edge i : graph) {
        char vertex = i.from;
        if (count(vertices.begin(), vertices.end(), vertex) == 0) vertices.push_back(vertex);

    }
    return vertices.size();
}

vector<char> vertices(vector<edge> graph) {
    vector<char> vertices = {};
    for (edge i : graph) {
        char vertex = i.from;
        if (count(vertices.begin(), vertices.end(), vertex) == 0) vertices.push_back(vertex);

    }
    return vertices;
}

vector<edge> edges_from_vertex(char vertex, vector<edge> big) {
    vector<edge> v;
    for (edge i : big) {
        if (i.from == vertex) v.push_back(i);
    }
    return v;
}

edge add_edge(vector<edge> big, vector<char> visited) {
    vector<char> all_vertices = vertices(big);
    int minimum = 100000000;
    edge smallest;
    for (char vertex : visited) {
        vector<edge> fromhere = edges_from_vertex(vertex, big);
        for (edge i : fromhere) {
            if (i.weight < minimum && (count(visited.begin(), visited.end(), i.to) == 0)) {
                minimum = i.weight;
                smallest = i;
            }
        }

    }
    return smallest;


}

vector<edge> prims_Algorithm(vector<edge> big, char start_point) {
    vector<char> visited = { start_point };
    vector<edge> SST ;

    vector<char> v1;
    vector<char> v2;
    vector<int> weights;

    while (visited.size() < num_vertices(big)) {
        edge edge_added = add_edge(big, visited);
        SST.push_back(edge_added);
        visited.push_back(edge_added.to);
        
    }
    return SST;
}

int main()
{
    vector<char> v1 = {'A','A','A','D','C','D','C','C','B','F','F'};
    vector<char> v2 = {'B','C','D','C','B','F','F','E','E','E','G'};
    vector<int> weights = {2,3,3,5,4,7,6,1,3,8,9};

    vector<edge> graph = create_graph(v1, v2, weights);

    //print_graph(graph);
    vector<edge> SST = prims_Algorithm(graph, 'A');
    print_graph(SST);
}
