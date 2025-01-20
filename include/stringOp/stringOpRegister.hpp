#ifndef STRINGOPREGISTER_HPP
#define STRINGOPREGISTER_HPP

#include <stringOp/stringOpFactory.hpp>

template <typename T>
class StringOpRegister{
public:
    StringOpRegister(StringOpType type){
        StringOpFactory::getInstance().registerStringOp(type, [](const std::vector<std::string>& args) -> std::unique_ptr<StringOperation>{
            return T::create(args);
        });
    }
};

#endif