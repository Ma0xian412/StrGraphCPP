#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <Util.hpp>
#include <Node.hpp>

class Graph{
protected:

    mutable std::mutex _node_mutex; //锁，保护节点
    mutable std::mutex _edge_mutex; //锁，保护边

    uint32_t _node_id; //节点id
    uint32_t _edge_id; //边id

    std::unordered_map<uint32_t, std::shared_ptr<Node>> _nodes; //节点

    std::vector<std::shared_ptr<Node>> topo_sort() const; //拓扑排序

    bool has_cycle() const; //是否有环

    void add_node_into_graph(const std::shared_ptr<Node>& node);


public:

    Graph();

    std::shared_ptr<Node> add_node(std::string type, std::vector<std::string> args);

    std::shared_ptr<Node> add_node_py(py::function func);

    void connect(std::shared_ptr<Node> from, std::shared_ptr<Node> to);

    std::unordered_map<uint32_t, std::shared_ptr<Node>> get_nodes() const;
};

#endif