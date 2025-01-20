#ifndef STRINGOPFACTORY_HPP
#define STRINGOPFACTORY_HPP

#include <stringOp/stringOp.hpp>

class StringOpFactory{
public:
    using CreatorFunc = std::function<std::unique_ptr<StringOperation>(const std::vector<std::string>&)>;

    static StringOpFactory& getInstance();

    void registerStringOp(StringOpType type, CreatorFunc creator);

    std::unique_ptr<StringOperation> createStringOp(StringOpType type, const std::vector<std::string>& args) const;

    std::unique_ptr<StringOperation> createPyFuncOp(const py::function& func) const;
private:
    StringOpFactory() = default;

    StringOpFactory(const StringOpFactory&) = delete;
    StringOpFactory& operator=(const StringOpFactory&) = delete;
    StringOpFactory(StringOpFactory&&) = delete;
    StringOpFactory& operator=(StringOpFactory&&) = delete;

    std::unordered_map<StringOpType, CreatorFunc> _registry;

};

#endif