#include <stringOp/stringOpRegister.hpp>
#include <stringOp/stringOp.hpp>

StringOpRegister<InputOp> InputOp::reg(StringOpType::Input);

InputOp::InputOp(std::string input_str):_inputs(input_str){}

std::string InputOp::execute(const std::vector<std::string>& inputs, const std::vector<std::string>& constants){
    return _inputs;
}

std::unique_ptr<StringOperation> InputOp::create(const std::vector<std::string>& args){
    return std::make_unique<InputOp>(args[0]);
}
