#ifndef ALGORITHMS_HW3_MAXFLOW_H
#define ALGORITHMS_HW3_MAXFLOW_H

#include <vector>

struct edge_s;

class node_t {
private:
    int value;
    std::vector<edge_s*> edges_out = {};

public:
    explicit node_t(int value);

    void add_edge(edge_s* new_edge);
    std::vector<edge_s*>& get_edges();
    int get_value() const;
};

struct edge_s {
    node_t* node;
    int capacity;
    int used;
};

edge_s* get_edge(node_t* S, node_t* T);

std::vector<node_t*> bfs(node_t* S, node_t* T);

int get_bottleneck(const std::vector<node_t*>& path);

void augment(const std::vector<node_t*>& path, int bottleneck);

int maxflow(node_t* S, node_t* T);

#endif //ALGORITHMS_HW3_MAXFLOW_H