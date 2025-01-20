#include <stringOp/stringOpFactory.hpp>

StringOpFactory& StringOpFactory::getInstance(){
    static StringOpFactory instance;
    return instance;
}

void StringOpFactory::registerStringOp(StringOpType type, CreatorFunc creator){
    _registry.emplace(type, creator);
}

std::unique_ptr<StringOperation> StringOpFactory::createStringOp(StringOpType type, const std::vector<std::string>& args) const{
    auto it = _registry.find(type);
    if(it == _registry.end()){
        
        throw std::invalid_argument("Invalid String Operation Type, this type doesn't exist or hasn't been registered");
    }
    return it -> second(args);
}

std::unique_ptr<StringOperation> StringOpFactory::createPyFuncOp(const py::function& func) const{
    return py_func_op::create(func);
}