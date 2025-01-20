cmake_minimum_required(VERSION 3.22)
project(StrGraphCpp
        VERSION 1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

# 寻找 pybind11
add_subdirectory(extern/pybind11)

# 添加源文件
set(SOURCES
    src/csrc/Graph.cpp
    src/csrc/Node.cpp
    src/csrc/Scheduler.cpp
    src/csrc/Binding.cpp
    src/csrc/stringOp/ConcateOp.cpp
    src/csrc/stringOp/InputOp.cpp
    src/csrc/stringOp/IOReadOp.cpp
    src/csrc/stringOp/IOWriteOp.cpp
    src/csrc/stringOp/stringOpFactory.cpp
    src/csrc/stringOp/pystringOp.cpp
)

add_library(stringop_lib STATIC
            src/csrc/stringOp/ConcateOp.cpp
            src/csrc/stringOp/InputOp.cpp
            src/csrc/stringOp/IOReadOp.cpp
            src/csrc/stringOp/IOWriteOp.cpp
            src/csrc/stringOp/stringOpFactory.cpp
            src/csrc/stringOp/pyStringOp.cpp
)

set_target_properties(stringop_lib PROPERTIES POSITION_INDEPENDENT_CODE ON)

# 将 stringop_lib 链接到 pybind11::pybind11，以包含 pybind11 的头文件路径
target_link_libraries(stringop_lib PRIVATE pybind11::pybind11)

target_include_directories(stringop_lib PRIVATE 
    ${CMAKE_SOURCE_DIR}/include 
    ${CMAKE_SOURCE_DIR}/include/stringOp 
    ${CMAKE_SOURCE_DIR}/include/spdlog
)

set(PYUSECSOURCES
    src/csrc/Graph.cpp
    src/csrc/Node.cpp
    src/csrc/Scheduler.cpp
    src/csrc/Binding.cpp
)

# 创建 Python 模块
pybind11_add_module(strgraphcpp ${PYUSECSOURCES})

# 设置 strgraphcpp 为位置无关代码
set_target_properties(strgraphcpp PROPERTIES POSITION_INDEPENDENT_CODE ON)

# 链接静态库
target_link_libraries(strgraphcpp PRIVATE -Wl,--whole-archive stringop_lib -Wl,--no-whole-archive)

# 指定包含目录，仅针对 strgraphcpp 和 stringop_lib 目标
target_include_directories(strgraphcpp PRIVATE 
    ${CMAKE_SOURCE_DIR}/include 
    ${CMAKE_SOURCE_DIR}/include/stringOp 
    ${CMAKE_SOURCE_DIR}/include/spdlog
)


# 编译选项优化
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(strgraphcpp PRIVATE -O3 -march=native -DNDEBUG)
    target_compile_options(stringop_lib PRIVATE -O3 -march=native -DNDEBUG)
else()
    target_compile_options(strgraphcpp PRIVATE -O0 -g)
    target_compile_options(stringop_lib PRIVATE -O0 -g)
endif()

# 链接线程库
find_package(Threads REQUIRED)
target_link_libraries(strgraphcpp PRIVATE Threads::Threads)

# 安装规则
install(TARGETS strgraphcpp
    LIBRARY DESTINATION _strgraphcpp
)












