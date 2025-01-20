import strgraphcpp
from strgraphcpp import Node, Graph, Scheduler


def main():

    #Init a graph
    graph = Graph()

    #Init two input nodes
    inputnode1 = graph.add_node("Input", ["aaa"])
    inputnode2 = graph.add_node("Input", ["bbb"])
    
    #Init a concatenation node
    concatenode1 = graph.add_node("Concate", [])

    #Connect the input nodes to the concatenation node
    graph.connect(inputnode1,concatenode1)
    graph.connect(inputnode2,concatenode1)

    #Execute the graph
    Scheduler(graph).execute([])

    #Print the output of the concatenation node
    print(concatenode1.get_output())

    #Define a python function
    def concate(inputs, constants):
        result = ""
        for str in inputs:
            result += str
        return result
    
    #Init a concatenation node define by python
    concatenode2 = graph.add_node_py(concate)

    


    
    
if __name__ == "__main__":
    main()

