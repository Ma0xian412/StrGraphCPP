#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <mutex>
#include <vector>
#include <string>
#include <functional>
#include <memory>
#include <unordered_map> 
#include <queue>
#include <future>
#include <fstream>
#include <thread>
#include <BS_thread_pool.hpp>
#include <spdlog/spdlog.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

using ComputeFunc = std::function<std::string(const std::vector<std::string>&, const std::vector<std::string>&)>;

namespace py = pybind11;

#endif // UTIL_HPP