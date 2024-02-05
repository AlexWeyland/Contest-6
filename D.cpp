#include <vector>
#include <iostream>
#include <queue>

using std::vector;
using std::queue;

struct Edge {
    size_t to;
    size_t price;
};

vector<vector<Edge>> graph;
const size_t inf = 1000000;

void Read() {
    size_t number, roads;
    std::cin >> number >> roads;
    graph.resize(number, vector<Edge>(0));
    for (size_t index = 0; index < roads; ++index) {
        size_t from, to, price;
        std::cin >> from >> to >> price;
        graph[from - 1].push_back({to - 1, price});
    }
}

void Relaxing(vector<size_t> &distance, vector<queue<size_t>> &prior_queue,
              vector<vector<bool>> &used, size_t level, size_t next) {
    for (auto &elem : graph[next]) {
        size_t plus = (level + elem.price) % 3;
        if (used[plus][elem.to] == false) {
            used[plus][elem.to] = true;

            if (distance[next] + elem.price < distance[elem.to]) {
                prior_queue[plus].push(elem.to);
                distance[elem.to] = distance[next] + elem.price;
            }
        }
    }
    prior_queue[level].pop();
}

size_t Dijkstra(size_t from, size_t to) {
    vector<queue<size_t>> prior_queue(3);
    vector<vector<bool>> used;
    vector<size_t> distance;

    used.resize(3, vector<bool>(graph.size(), false));
    distance.resize(graph.size(), inf);
    prior_queue[0].push(from);
    distance[from] = 0;
    used[0][from] = true;
    size_t level = 0;

    while (!prior_queue[0].empty() || !prior_queue[1].empty() || !prior_queue[2].empty()) {
        if (prior_queue[level].empty()) {
            level = (level + 1) % 3;
            continue;
        }

        if (prior_queue[level].front() == to) {
            break;
        }

        Relaxing(distance, prior_queue, used, level, prior_queue[level].front());
    }
    return distance[to];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Read();

    size_t request;
    std::cin >> request;
    for (size_t index = 0; index < request; ++index) {
        size_t from, to;
        std::cin >> from >> to;

        auto result = Dijkstra(from - 1, to - 1);
        if (result == inf) {
            std::cout << -1 << '\n';
        } else {
            std::cout << result << '\n';
        }
    }
    return 0;
}
