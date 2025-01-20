# StrGraphCpp

**StrGraphCpp** is a high-performance graph computation system designed to model and process data dependency relationships and computations as Directed Acyclic Graphs (DAGs). In this system, nodes represent string values, and computation logic is fully customizable by the user.

Key features of **StrGraphCpp** include:

1. **Flexible User-Defined Computation Logic**:  
   The system employs an auto-registration factory pattern, allowing users to define custom computation logic. For computations that are not performance-critical, users can define the logic in Python for ease of use and rapid development. For performance-sensitive computations, users can implement the logic in C++ to leverage its efficiency and speed. This design ensures both flexibility and scalability, catering to diverse application scenarios while optimizing performance where needed.

2. **C++ and Python Interoperability**:  
   The project leverages **pybind11** to bridge C++ and Python, allowing for the seamless integration of Python-based workflows and the high-performance capabilities of C++.

3. **Efficient Parallel Computation**:  
   A thread pool is implemented to maximize concurrency and minimize computation time. The system is designed to efficiently handle multiple tasks in parallel, improving throughput and performance.

4. **Optimized Data Dependency Management**:  
   By isolating data dependency relationships, the system adopts a lock-free design to enhance computational efficiency. This reduces contention and ensures robust performance even under high workloads.


## Enviroment
- g++ 11.4.0
- cmake 3.22.1
- Ubuntu 22.04.4 LTS
- python 3.12.7
- pybind11 2.13.6

## Build
```bash
pip install .
```

## Interface

## Node Class API

- **Node()**  
  Default constructor.

- **~Node()**  
  Default destructor.

- **get_id()**  
  Returns the node ID.

- **set_id(uint32_t id)**  
  Sets the node ID.

- **get_output()**  
  Returns the current output as a string.

- **set_output(const std::string& output)**  
  Sets the output string.

- **set_compute_func(ComputeFunc compute_func)**  
  Assigns a custom compute function.

- **set_string_op(std::unique_ptr<StringOperation> string_op)**  
  Assigns a string operation object.

- **add_out_node(std::shared_ptr<Node> node)**  
  Appends one output node.

- **add_out_nodes(nodes_list nodes)**  
  Appends multiple output nodes.

- **add_in_node(std::shared_ptr<Node> node)**  
  Appends one input node.

- **add_in_nodes(nodes_list nodes)**  
  Appends multiple input nodes.

- **get_out_nodes()**  
  Returns a list of output nodes.

- **get_in_nodes()**  
  Returns a list of input nodes.

- **set_constant(std::string constant)**  
  Sets a string constant.

- **get_constant()**  
  Returns the current constant string.

- **compute(const std::vector<std::string>& inputs, const std::vector<std::string>& constants)**  
  Performs the compute function using the given inputs and constants, returning a string result.

## Graph Class API

- **Graph()**  
  Default constructor.

- **add_node(std::string type, std::vector<std::string> args)**  
  Creates and adds a new node of the specified type, using the provided arguments.

- **add_node_py(py::function func)**  
  Creates and adds a new node using a Python function.

- **connect(std::shared_ptr<Node> from, std::shared_ptr<Node> to)**  
  Connects one node's output to another node's input.

- **get_nodes()**  
  Returns a map of node IDs to shared pointers of the corresponding nodes.

## Scheduler Class API

- **execute_node(const std::shared_ptr<Node>& node, const std::vector<std::string>& constant)**  
  Executes the specified node with the given constant string parameters.

- **Scheduler(const std::shared_ptr<Graph>& graph)**  
  Constructs a Scheduler with the specified graph.

- **execute(const std::vector<std::string>& constant = {})**  
  Executes the entire graph, optionally with user-supplied constants.

## StringOperation Class API

- **~StringOperation()**  
  Default virtual destructor.

- **execute(const std::vector<std::string>& inputs, const std::vector<std::string>& constants)**  
  Performs a custom string operation using the provided inputs and constants, returning a string result.

### Custom String Operation

### CPP
Users can define their own custom string operations by inheriting from the `StringOperation` class and implementing the `execute` method. Additionally, users should implement a `create` method and a corresponding registrar to facilitate the creation and registration of the custom operation.

### Example

```cpp
class InputOp : public StringOperation{
private:
    static StringOpRegister<InputOp> reg;

    std::string _inputs;

public:
    InputOp(std::string input_str);

    std::string execute(const std::vector<std::string>& inputs, const std::vector<std::string>& constants) override;

    static std::unique_ptr<StringOperation> create(const std::vector<std::string>& args);
};

static StringOpRegister<io_read_op> regConcate(StringOpType::IORead);

io_read_op::io_read_op(std::string file_path):_file_path(file_path){}

std::string io_read_op::execute(const std::vector<std::string>& inputs, const std::vector<std::string>& constants){

    std::ifstream file(_file_path);
    if (!file.is_open()) {
        return "";
    }
    std::string result;
    std::string line;
    while (std::getline(file, line)) {
        result += line;
    }
    return result;
}

std::unique_ptr<StringOperation> io_read_op::create(const std::vector<std::string>& args){
    if(args.size() != 1){
        throw std::invalid_argument("Invalid arguments for IOReadOp");
    }
    return std::make_unique<io_read_op>(args[0]);
}
```

By following this pattern, users can easily extend the functionality of the `StringOperation` class with their own custom operations.

### Python

You can define custom compute logic in Python and integrate it into the graph using the `add_node_py` method. Below is an example of how to do this.
```
# Define a Python function
    def concate(inputs, constants):
        result = ""
        for str in inputs:
            result += str
        return result

# Initialize a concatenation node defined by Python
    concatenode2 = graph.add_node_py(concate)
```

## Python API Documentation

### Module: `strgraphcpp`

This module provides Python bindings for the C++ classes `Node`, `Graph`, and `Scheduler`.

### Classes

#### `Node`

- **`Node()`**  
  Default constructor.

- **`set_compute_func_by_py(func: py::function)`**  
  Sets the compute function using a Python function.

- **`set_compute_func_by_c(type_str: str, args: List[str])`**  
  Sets the compute function using a C++ string operation type and arguments.

- **`compute(inputs: List[str], constants: List[str]) -> str`**  
  Executes the compute function with the given inputs and constants, returning the result.

- **`get_id() -> int`**  
  Returns the node ID.

- **`set_constant(constant: str)`**  
  Sets a constant string for the node.

- **`get_output() -> str`**  
  Returns the current output string of the node.

- **`set_output(output: str)`**  
  Sets the output string of the node.

- **`get_out_nodes() -> List[Node]`**  
  Returns a list of output nodes.

- **`get_in_nodes() -> List[Node]`**  
  Returns a list of input nodes.

#### `Graph`

- **`Graph()`**  
  Default constructor.

- **`get_nodes() -> Dict[int, Node]`**  
  Returns a dictionary of node IDs to nodes.

- **`add_node(type: str, args: List[str]) -> Node`**  
  Adds a new node of the specified type with the given arguments.

- **`add_node_py(func: py::function) -> Node`**  
  Adds a new node using a Python function.

- **`connect(from: Node, to: Node)`**  
  Connects one node's output to another node's input.

#### `Scheduler`

- **`Scheduler(graph: Graph)`**  
  Constructs a Scheduler with the specified graph.

- **`execute(constants: List[str] = [])`**  
  Executes the graph with the optional list of constants.