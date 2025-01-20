#include <Scheduler.hpp>

Scheduler::Scheduler(const std::shared_ptr<Graph>& graph):_graph(graph), _pool(std::thread::hardware_concurrency()){}

void Scheduler::execute(const std::vector<std::string>& constants){

    spdlog::info("Executing graph");
    py::gil_scoped_release release;

    try
    {
        auto exec_order = _graph -> get_nodes();//后续修改为只获取节点 不进行实际排序，因为动态生成 不用事先进行拓扑，也可以事先进行拓扑判断是否有环

        size_t num_nodes = exec_order.size();
        spdlog::info("Number of nodes: {}", num_nodes);
        
        _output_map.resize(num_nodes);
        
        //存放所有出度为0的点为终点
        std::queue<uint32_t> end_nodes;

        std::vector<std::function<void()>> tasks;
        
        for(const auto& [id, node]: exec_order){
            _dependency_counts[node -> get_id()] = node -> get_in_nodes().size();
            if(node -> get_in_nodes().size() == 0){
                tasks.push_back([this, node, &constants](){
                    execute_node(node, constants);
                });
            }
            if(node -> get_out_nodes().size() == 0){
                end_nodes.push(id);
            }
        }

        for(const auto& task: tasks){
            _pool.detach_task(task);
        }

        tasks.clear();
        tasks.shrink_to_fit();

        spdlog::info("Waiting for graph execution to complete");
        _pool.wait();

        spdlog::info("Graph execution completed");
        while(!end_nodes.empty()){
            uint32_t end_id = end_nodes.front();
            end_nodes.pop();
            spdlog::info("End node id: {}", end_id);
            spdlog::info("End node output: {}", _output_map[end_id]);
        }
    }
    catch(const pybind11::error_already_set& e)
    {
        spdlog::error("Exception occurred: {}", e.what());
        throw;
    }
}

void Scheduler::execute_node(const std::shared_ptr<Node>& node, const std::vector<std::string>& constant){
    try
    {   
        std::vector<std::string> inputs;
        inputs.reserve(node -> get_in_nodes().size());

        for(const auto& from_node: node -> get_in_nodes()){
            uint32_t input_id = from_node -> get_id();
            std::string from_output;
            try
            {
                from_output = _output_map.at(input_id);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                throw;
            }
            
            inputs.emplace_back(from_output);
        }

        //每个constant的最后一个元素都是本计算节点自带的constant
        std::vector<std::string> tmpconstants(constant);
        tmpconstants.emplace_back(node -> get_constant());
        
        std::string output = node -> compute(inputs, tmpconstants);
        _output_map[node -> get_id()] = output;

        node -> set_output(output);

        for(const auto& to_node: node -> get_out_nodes()){
            uint32_t to_id = to_node -> get_id();
            if(--_dependency_counts[to_id] == 0){
                _pool.detach_task([this, to_node, &constant](){
                    execute_node(to_node, constant);
                });
            }
        }


    }
    catch(const std::exception& e)
    {
        throw pybind11::value_error(e.what());
    }
    
}