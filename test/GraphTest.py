import strgraphcpp
from strgraphcpp import Node, Graph, Scheduler

def main():
    graph = Graph()

    inputnode1 = graph.add_node("Input", ["ccc"])
    inputnode2 = graph.add_node("Input", ["bbb"])
    
    def concate(inputs, constants):
        result = ""
        for str in inputs:
            result += str
        return result

    concatenode2 = graph.add_node_py(concate)

    graph.connect(inputnode1,concatenode2)
    graph.connect(inputnode2,concatenode2)

    Scheduler(graph).execute([])

    print(concatenode2.get_output())


if __name__ == "__main__":
    main()