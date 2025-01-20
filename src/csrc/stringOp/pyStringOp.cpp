#include <stringOp/stringOp.hpp>
#include <stringOp/stringOpRegister.hpp>

py_func_op::py_func_op(py::function func):_func(func){}

std::string py_func_op::execute(const std::vector<std::string>& inputs, const std::vector<std::string>& constants){
    py::gil_scoped_acquire acquire;
    py::list input_list;
    for(const auto& input: inputs){
        input_list.append(input);
    }
    py::list const_list;
    for(const auto& cons: constants){
        const_list.append(cons);
    }
    if(_func == nullptr){
        // throw std::invalid_argument("Invalid function");
        return "";
    }
    py::object result = _func(input_list, const_list);
    return result.cast<std::string>();
}

std::unique_ptr<StringOperation> py_func_op::create(const py::function& func){
    return std::make_unique<py_func_op>(func);
}



