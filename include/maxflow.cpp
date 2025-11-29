#include <iostream>
#include <climits>
#include <queue>
#include <unordered_set>
#include <vector>

#include "maxflow.h"


node_t::node_t(const int value): value(value) {}

void node_t::add_edge(edge_s* new_edge) { edges_out.push_back(new_edge); }

std::vector<edge_s*>& node_t::get_edges() { return edges_out; }

int node_t::get_value() const { return value; }

edge_s* get_edge(node_t* S, node_t* T) {
    for (auto* edge: S->get_edges()) {
        if (edge->node == T) {
            return edge;
        }
    }
    return nullptr;
}

std::vector<node_t*> bfs(node_t* S, node_t* T) {
    std::queue<std::pair<node_t*, std::vector<node_t*>>> q;
    q.push({S, {S}});
    std::unordered_set<node_t*> seen;
    seen.insert(S);

    while (!q.empty()) {
        auto [node, path] = q.front();
        q.pop();

        if (node == T) { return path; }

        for (auto* edge: node->get_edges()) {
            if (!seen.count(edge->node) && edge->capacity - edge->used > 0) {
                auto new_path = path;
                new_path.push_back(edge->node);
                q.emplace(edge->node, std::move(new_path));
                seen.insert(edge->node);
            }
        }
    }
    return {};
}

int get_bottleneck(const std::vector<node_t*>& path) {
    int bottleneck = INT_MAX;

    for (int i = 0; i < path.size() - 1; ++i) {
        auto u = path[i];
        auto v = path[i + 1];

        auto edge = get_edge(u, v);
        int residual_capacity = edge->capacity - edge->used;
        bottleneck = std::min(bottleneck, residual_capacity);
    }
    return bottleneck;
}

void augment(const std::vector<node_t*>& path, int bottleneck) {
    for (int i = 0; i < path.size() - 1; ++i) {
        auto u = path[i];
        auto v = path[i + 1];

        auto forward = get_edge(u, v);
        auto backward = get_edge(v, u);

        forward->used += bottleneck;
        backward->used -= bottleneck;
    }
}

int maxflow(node_t* S, node_t* T) {
    int flows = 0;
    std::unordered_set<node_t*> seen;

    while (true) {
        auto path = bfs(S, T);
        if (path.empty()) break;

        auto bottleneck = get_bottleneck(path);
        if (bottleneck <= 0) break;

        augment(path, bottleneck);
        flows += bottleneck;
    }

    return flows;
}
