#include <stringOp/stringOp.hpp>
#include <stringOp/stringOpRegister.hpp>

StringOpRegister<ConcateOp> ConcateOp::reg(StringOpType::Concate);

std::string ConcateOp::execute(const std::vector<std::string>& inputs, const std::vector<std::string>& constants){
    std::string result = constants.empty() ? "" : constants[0];
    for (const auto& s : inputs) {
        result += s;
    }
    return result;
}

std::unique_ptr<StringOperation> ConcateOp::create(const std::vector<std::string>& args){
    return std::make_unique<ConcateOp>();
}