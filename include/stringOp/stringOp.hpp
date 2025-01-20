#ifndef STRINGOP_HPP
#define STRINGOP_HPP

#include <Util.hpp>

enum StringOpType{
    Concate,
    Input,
    Uppercase,
    Lowercase,
    IORead,
    IOWrite,
    py_func,

    //....
    //可新增 支持新的字符串操作类型
};

inline StringOpType stringToStringOpType(const std::string& str){
    if(str == "Concate"){
        return StringOpType::Concate;
    }else if(str == "Input"){
        return StringOpType::Input;
    }else if(str == "Uppercase"){
        return StringOpType::Uppercase;
    }else if(str == "Lowercase"){
        return StringOpType::Lowercase;
    }else if(str == "IORead"){
        return StringOpType::IORead;
    }else if(str == "IOWrite"){
        return StringOpType::IOWrite;
    }else if(str == "py_func"){
        return StringOpType::py_func;
    }else{
        throw std::invalid_argument("Invalid String Operation Type");
    }

    //....
    //可新增 支持新的字符串操作类型
}

template <typename T>
class StringOpRegister;

class StringOperation {
public:
    virtual ~StringOperation() = default;
    virtual std::string execute(const std::vector<std::string>& inputs, const std::vector<std::string>& constants) = 0;
};

class py_func_op : public StringOperation{
private:
    static StringOpRegister<py_func_op> reg;

    py::function _func;

public:
    py_func_op(py::function func);

    std::string execute(const std::vector<std::string>& inputs, const std::vector<std::string>& constants) override;

    static std::unique_ptr<StringOperation> create(const py::function& func);
};

class InputOp : public StringOperation{
private:
    static StringOpRegister<InputOp> reg;

    std::string _inputs;

public:
    InputOp(std::string input_str);

    std::string execute(const std::vector<std::string>& inputs, const std::vector<std::string>& constants) override;

    static std::unique_ptr<StringOperation> create(const std::vector<std::string>& args);
};

class io_read_op : public StringOperation{
private:
    static StringOpRegister<io_read_op> reg;

    std::string _file_path;

public:
    io_read_op(std::string file_path);

    std::string execute(const std::vector<std::string>& inputs, const std::vector<std::string>& constants) override;

    static std::unique_ptr<StringOperation> create(const std::vector<std::string>& args);
};

class io_write_op : public StringOperation{
private:
    static StringOpRegister<io_write_op> reg;

    std::string _file_path;

public:
    io_write_op(std::string file_path);

    std::string execute(const std::vector<std::string>& inputs, const std::vector<std::string>& constants) override;

    static std::unique_ptr<StringOperation> create(const std::vector<std::string>& args);
};

class ConcateOp : public StringOperation{
private:
    static StringOpRegister<ConcateOp> reg;

public:
    ConcateOp() = default;

    std::string execute(const std::vector<std::string>& inputs, const std::vector<std::string>& constants) override;

    static std::unique_ptr<StringOperation> create(const std::vector<std::string>& args);
};






#endif // STRINGOP_HPP