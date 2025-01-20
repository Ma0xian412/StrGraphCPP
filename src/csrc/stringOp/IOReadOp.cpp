#include <stringOp/stringOp.hpp>
#include <stringOp/stringOpRegister.hpp>

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