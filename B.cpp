#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <set>

using std::vector;
using std::string;

struct Edge {
    int neighbour;
    int price;
};

int n_vertex, n_edge;
vector<bool> used;
vector<vector<Edge>> graph, graph_t;
int global_min = 1000001;
const int inf = 100000000;
bool cycle_found = false;
vector<int> order;
std::set<int> component;

void Read() {
    std::cin >> n_vertex >> n_edge;

    graph.resize(n_vertex, vector<Edge>(1, {0, 0}));
    graph_t.resize(n_vertex, vector<Edge>(1, {0, 0}));
    for (int index = 0; index < n_edge; ++index) {
        int from, to, price;
        std::cin >> from >> to >> price;
        --from;
        --to;
        graph[from].push_back({to, price});
        graph_t[to].push_back({from, price});
    }
}

void Find_negative_cycle(const std::set<int>& component, int current_min) {
    vector<int> difference;
    difference.resize(n_vertex, inf);
    difference[current_min] = 0;
    for (size_t index = 1; index < component.size(); ++index) {
        for (auto &vertex: component) {
            for (size_t item = 1; item < graph[vertex].size(); ++item) {
                Edge edge = graph[vertex][item];
                if (component.find(edge.neighbour) != component.end()) {
                    int start = vertex;
                    int finish = edge.neighbour;
                    int weight = edge.price;
                    if (difference[start] + weight < difference[finish]) {
                        difference[finish] = difference[start] + weight;
                    }
                }
            }
        }
    }

    for (auto &vertex: component) {
        for (size_t item = 1; item < graph[vertex].size(); ++item) {
            Edge edge = graph[vertex][item];
            if (component.find(edge.neighbour) != component.end()) {
                int start = vertex;
                int finish = edge.neighbour;
                int weight = edge.price;
                if (difference[start] + weight < difference[finish]) {
                    difference[finish] = difference[start] + weight;
                    cycle_found = true;
                    if (current_min < global_min) {
                        global_min = current_min;
                    }
                }
            }
        }
    }
}

void dfs1(int vertex) {
    used[vertex] = true;
    for (size_t index = 1; index < graph[vertex].size(); ++index) {
        if (!used[graph[vertex][index].neighbour]) {
            dfs1(graph[vertex][index].neighbour);
        }
    }
    order.push_back(vertex);
}

void dfs2(int vertex, int& current_min) {
    used[vertex] = true;
    component.insert(vertex);
    if (vertex < current_min) {
        current_min = vertex;
    }
    for (size_t index = 1; index < graph_t[vertex].size(); ++index) {
        if (!used[graph_t[vertex][index].neighbour]) {
            dfs2(graph_t[vertex][index].neighbour, current_min);
        }
    }
}

void DFS() {
    used.assign(n_vertex, false);
    for (int index = 0; index < n_vertex; ++index) {
        if (!used[index]) {
            dfs1(index);
        }
    }
    used.assign(n_vertex, false);
    for (int index = 0; index < n_vertex; ++index) {
        int vertex = order[n_vertex - 1 - index];
        if (!used[vertex]) {
            int current_min = inf;
            dfs2(vertex, current_min);
            Find_negative_cycle(component, current_min);
            component.clear();
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Read();

    used.resize(n_vertex, false);

    DFS();

    if (cycle_found == false) {
        std::cout << "NO";
    } else {
        std::cout << "YES" << '\n' << global_min + 1;
    }
    return 0;
}
