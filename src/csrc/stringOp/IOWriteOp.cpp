#include <stringOp/stringOp.hpp>
#include <stringOp/stringOpRegister.hpp>

static StringOpRegister<io_write_op> reg(StringOpType::IOWrite);

io_write_op::io_write_op(std::string file_path):_file_path(file_path){}

std::string io_write_op::execute(const std::vector<std::string>& inputs, const std::vector<std::string>& constants){
    std::ofstream file(_file_path);
    if (!file.is_open()) return "";
    for (const auto& s : inputs) {
        file << s << std::endl;
    }
    file.close();
    return "";
}

std::unique_ptr<StringOperation> io_write_op::create(const std::vector<std::string>& args){
    if(args.size() != 1){
        throw std::invalid_argument("Invalid arguments for IOWriteOp");
    }
    return std::make_unique<io_write_op>(args[0]);
}