#include <Graph.hpp>
#include <Node.hpp>
#include <Scheduler.hpp>
#include <stringOp/stringOp.hpp>
#include <stringOp/stringOpFactory.hpp>
#include <stringOp/stringOpRegister.hpp>

PYBIND11_MODULE(strgraphcpp, m){
    py::class_<Node, std::shared_ptr<Node>>(m, "Node")
        .def(py::init())
        .def("set_compute_func_by_py", [](Node& node, py::function func){
            auto string_op = StringOpFactory::getInstance().createPyFuncOp(func);
            node.set_string_op(std::move(string_op));
        })
        .def("set_compute_func_by_c", [](Node& node, const std::string& type_str, const std::vector<std::string>& args){
            StringOpType type = stringToStringOpType(type_str);
            auto string_op = StringOpFactory::getInstance().createStringOp(type, args);
            node.set_string_op(std::move(string_op));
        })
        .def("compute", &Node::compute)
        .def("get_id", &Node::get_id)
        .def("set_constant", &Node::set_constant)
        .def("get_output", &Node::get_output)
        .def("set_output", &Node::set_output)
        .def("get_out_nodes", &Node::get_out_nodes)
        .def("get_in_nodes", &Node::get_in_nodes); 

    py::class_<Graph, std::shared_ptr<Graph>>(m, "Graph")
        .def(py::init<>())
        .def("get_nodes", &Graph::get_nodes, py::return_value_policy::reference_internal)
        .def("add_node", &Graph::add_node)
        .def("add_node_py", &Graph::add_node_py)
        .def("connect", &Graph::connect);

    py::class_<Scheduler, std::shared_ptr<Scheduler>>(m, "Scheduler")
        .def(py::init<std::shared_ptr<Graph>>())
        .def("execute", &Scheduler::execute, py::arg("constants"));
}