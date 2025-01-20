import strgraphcpp
from strgraphcpp import Node, Graph, Scheduler

def main():
    graph = Graph()

    #Generate 100 input nodes
    inputnodes = []
    for i in range(100):
        inputnodes.append(graph.add_node("Input", [str(i)]))

    #Generate a concatenation node
    concatenode = graph.add_node("Concate", [])

    #Connect all input nodes to the concatenation node
    for i in range(100):
        graph.connect(inputnodes[i],concatenode)

    #Execute the graph
    Scheduler(graph).execute([])
    print(concatenode.get_output())


if __name__ == "__main__":
    main()