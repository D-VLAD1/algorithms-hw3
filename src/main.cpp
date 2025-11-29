#include <iostream>
#include <queue>
#include <sstream>
#include <vector>

#include "maxflow.h"


struct pairs_s {
    std::vector<std::pair<int, int>> edges;
    int size;
};


pairs_s connect(int nodes_amount, const std::vector<bool>& forbidden,
            const std::vector<std::pair<int, int>>& edges) {

    auto* S = new node_t(-1);
    auto* T = new node_t(-2);

    std::vector<node_t*> nodes(nodes_amount);
    for (int i = 1; i <= nodes_amount; ++i) { nodes[i - 1] = new node_t(i); }

    std::vector<std::vector<int>> adj_list(nodes_amount);
    for (auto& [u, v]: edges) {
        if (forbidden[u - 1] || forbidden[v - 1]) continue;
        adj_list[u - 1].push_back(v - 1);
        adj_list[v - 1].push_back(u - 1);
    }

    std::vector color(nodes_amount, -1);
    for (int start = 0; start < nodes_amount; ++start) {
        if (color[start] != -1 || forbidden[start]) continue;

        std::queue<int> q;
        q.push(start);
        color[start] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (auto next: adj_list[u]) {
                if (color[next] == -1) {
                    color[next] = 1 - color[u];
                    q.push(next);
                }
            }
        }
    }

    std::vector<node_t*> left;
    std::vector<node_t*> right;
    for (int i = 0; i < color.size(); ++i) {
        if (color[i] == 0) {
            left.push_back(nodes[i]);

            auto* edge_s_i = new edge_s{nodes[i], 1, 0};
            S->add_edge(edge_s_i);

            auto* edge_i_s = new edge_s{S, 0, 0};
            nodes[i]->add_edge(edge_i_s);
        } else if (color[i] == 1) {
            right.push_back(nodes[i]);

            auto* edge_t_i = new edge_s{nodes[i], 0, 0};
            T->add_edge(edge_t_i);

            auto* edge_i_t = new edge_s{T, 1, 0};
            nodes[i]->add_edge(edge_i_t);
        }
    }

    for (auto [u, v]: edges) {
        --u;
        --v;
        if (color[u] == 0 && color[v] == 1) {
            auto* edge_u_v = new edge_s{nodes[v], 1, 0};
            nodes[u]->add_edge(edge_u_v);

            auto* edge_v_u = new edge_s{nodes[u], 0, 0};
            nodes[v]->add_edge(edge_v_u);
        } else if (color[u] == 1 && color[v] == 0) {
            auto* edge_u_v = new edge_s{nodes[v], 0, 0};
            nodes[u]->add_edge(edge_u_v);

            auto* edge_v_u = new edge_s{nodes[u], 1, 0};
            nodes[v]->add_edge(edge_v_u);
        }
    }

    int flows = maxflow(S, T);
    std::vector<std::pair<int, int>> output_edges;
    for (auto u: left) {
        for (auto edge: u->get_edges()) {
            if (edge->used == edge->capacity)
                output_edges.emplace_back(u->get_value(), edge->node->get_value());
        }
    }

    auto output = pairs_s{output_edges, flows};

    for (auto* node: nodes) { delete node; }
    delete S;
    delete T;

    return output;
}


int main() {
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);

    int nodes_amount;
    ss >> nodes_amount;

    std::vector<int> forbidden;
    std::getline(std::cin, line);
    std::stringstream ss1(line);

    int x;
    while (ss1 >> x) {
        forbidden.push_back(x);
    }

    int edge_amount;
    std::cin >> edge_amount;

    std::vector<std::pair<int, int>> edges;
    edges.resize(edge_amount);

    for (int i = 0; i < edge_amount; ++i) {
        int v, u;
        std::cin >> v >> u;
        edges[i] = {v, u};
    }

    std::vector forbidden_bool(nodes_amount, false);
    for (int v : forbidden) {
        if (1 <= v && v <= nodes_amount) {
            forbidden_bool[v - 1] = true;
        }
    }

    auto output = connect(nodes_amount, forbidden_bool, edges);
    std::cout << output.size << std::endl;
    for (auto [u, v]: output.edges) std::cout << u << " -- " << v << std::endl;

    return 0;
}

// 8
// 3 6
// 11
// 1 2
// 1 3
// 2 3
// 2 4
// 3 5
// 4 5
// 4 6
// 5 6
// 6 7
// 6 8
// 7 8
