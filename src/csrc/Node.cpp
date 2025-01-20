#include <Node.hpp>

uint32_t Node::get_id() const{
    return _id;
}

void Node::set_id(const uint32_t id){
    _id = id;
}

std::string Node::get_output() const{
    return _output;
}

void Node::set_output(const std::string& output){
    _output = output;
}

void Node::set_compute_func(ComputeFunc compute_func){
    _compute_func = compute_func;
}

void Node::set_string_op(std::unique_ptr<StringOperation> string_op){
    _string_op = std::move(string_op);
}

std::string Node::compute(const std::vector<std::string>& inputs, const std::vector<std::string>& constants){
    if(_string_op){
        auto result = _string_op -> execute(inputs, constants);
        set_output(result);
        return result;
    }
    return "";
}

std::string Node::get_constant() const{
    return _constant;
}

void Node::set_constant(std::string constant){
    _constant = constant;
}

void Node::add_out_node(std::shared_ptr<Node> node){
    _out_nodes.push_back(std::move(node));
}

void Node::add_out_nodes(nodes_list nodes){
    _out_nodes.insert(_out_nodes.end(), nodes.begin(), nodes.end());
}

void Node::add_in_node(std::shared_ptr<Node> node){
    _in_nodes.push_back(std::move(node));
}

void Node::add_in_nodes(nodes_list nodes){
    _in_nodes.insert(_in_nodes.end(), nodes.begin(), nodes.end());
}

const nodes_list& Node::get_out_nodes() const{
    return _out_nodes;
}

const nodes_list& Node::get_in_nodes() const{
    return _in_nodes;
}