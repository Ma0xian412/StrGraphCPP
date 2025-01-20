#ifndef NODE_HPP    
#define NODE_HPP

#include <Util.hpp>
#include <stringOp/stringOp.hpp>

class Edge;
class Node;

using nodes_list = std::vector<std::shared_ptr<Node>>;

class Node{
protected:

    uint32_t _id;//节点id, Graph用于标识节点

    nodes_list _out_nodes; // 出度节点
    nodes_list _in_nodes; // 入度节点

    std::string _constant;

    std::string _output; //输出

    ComputeFunc _compute_func; //计算函数, Node实际的action，弃用

    std::unique_ptr<StringOperation> _string_op; //字符串操作,node实际的action

public:

    Node() = default;

    ~Node() = default;

    uint32_t get_id() const;

    void set_id(const uint32_t id);

    std::string get_output() const;

    void set_output(const std::string& output);

    void set_compute_func(ComputeFunc compute_func);

    void set_string_op(std::unique_ptr<StringOperation> string_op);

    void add_out_node(std::shared_ptr<Node> node);

    void add_out_nodes(nodes_list nodes);

    void add_in_node(std::shared_ptr<Node> node);

    void add_in_nodes(nodes_list nodes);

    const nodes_list& get_out_nodes() const;

    const nodes_list& get_in_nodes() const;

    void set_constant(std::string constant);

    std::string get_constant() const;

    std::string compute(const std::vector<std::string>& inputs, const std::vector<std::string>& constants);
};

#endif // NODE_HPP