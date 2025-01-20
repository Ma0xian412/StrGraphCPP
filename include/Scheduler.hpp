#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <Util.hpp>
#include <Graph.hpp>


class Scheduler{
protected:

    std::shared_ptr<Graph> _graph;

    std::vector<std::string> _output_map;

    std::unordered_map<uint32_t, std::atomic<int>> _dependency_counts;

    std::mutex _output_mutex;

    BS::thread_pool<> _pool; //线程池

    void execute_node(const std::shared_ptr<Node>& node, const std::vector<std::string>& constant);

public:
    Scheduler(const std::shared_ptr<Graph>& graph);

    void execute(const std::vector<std::string>& constant = {});

};

#endif