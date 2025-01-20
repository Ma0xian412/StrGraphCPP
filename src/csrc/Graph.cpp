#include <Graph.hpp>
#include <stringOp/stringOpFactory.hpp>
Graph::Graph():_node_id(0), _edge_id(0){}

void Graph::add_node_into_graph(const std::shared_ptr<Node>& node){
    node -> set_id(_node_id);
    _nodes.emplace(_node_id, node);
    _node_id++;
}

void Graph::connect(std::shared_ptr<Node> from, std::shared_ptr<Node> to){
    uint32_t from_id = from -> get_id();
    if(_nodes.find(from_id) == _nodes.end()){
        throw std::runtime_error("From node with ID '" + std::to_string(from_id) + "' does not exist.");
    }

    uint32_t to_id = to -> get_id();
    if(_nodes.find(to_id) == _nodes.end()){
        throw std::runtime_error("To node with ID '" + std::to_string(to_id) + "' does not exist.");
    }

    from -> add_out_node(to);
    to -> add_in_node(from);
}


std::vector<std::shared_ptr<Node>> Graph::topo_sort() const{
    std::unordered_map<uint32_t, int> in_degrees;
    for(const auto& [id, node]: _nodes){
        in_degrees[id] = node -> get_in_nodes().size();
    }

    std::queue<uint32_t> q;
    for(const auto& [id, degree]: in_degrees){
        if(degree == 0){
            q.push(id);
        }
    }

    std::vector<std::shared_ptr<Node>> order;
    while(!q.empty()){
        uint32_t id = q.front();
        q.pop();

        auto node = _nodes.at(id);
        order.push_back(node);

        for(const auto& to_node: node -> get_out_nodes()){
            const uint32_t to_id = to_node -> get_id();
            in_degrees[to_id]--;
            if(in_degrees[to_id] == 0){
                q.push(to_id);
            }
        }
    }

    if(order.size() != _nodes.size()){
        throw std::runtime_error("Graph has a cycle.");
    }

    return order;
}

bool Graph::has_cycle() const{
    try
    {
        topo_sort();
        return false;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return true;
    }
}

std::unordered_map<uint32_t, std::shared_ptr<Node>> Graph::get_nodes() const{
    return _nodes;
}

std::shared_ptr<Node> Graph::add_node(std::string type, std::vector<std::string> args){
    try
    {
        auto node = std::make_shared<Node>();
        node -> set_string_op(StringOpFactory::getInstance().createStringOp(stringToStringOpType(type), args));
        add_node_into_graph(node);
        return node;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        throw;
    }
}

std::shared_ptr<Node> Graph::add_node_py(py::function func){
    try
    {
        auto node = std::make_shared<Node>();
        node -> set_string_op(StringOpFactory::getInstance().createPyFuncOp(func));
        add_node_into_graph(node);
        return node;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        throw;
    }
}

