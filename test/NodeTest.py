import strgraphcpp
from strgraphcpp import Node, Graph, Scheduler

def main():
    graph = Graph()

    #addTest_c
    inputnode1 = graph.add_node("Input", ["ccc"])
    inputnode2 = graph.add_node("Input", ["bbb"])
    

    #addTest_py
    def concate(inputs, constants):
        result = ""
        for str in inputs:
            result += str
        return result

    concatenode2 = graph.add_node_py(concate)

    #NodecomputeTest
    print(concatenode2.compute(["1",'2'],[]))


if __name__ == "__main__":
    main()