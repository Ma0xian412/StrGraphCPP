# setup.py
from setuptools import setup, find_packages
import os
from pybind11.setup_helpers import Pybind11Extension, build_ext

# 定义包含目录
include_dir = os.path.join(os.path.dirname(__file__), 'include')

# 收集所有需要编译的源文件
ext_modules = [
    Pybind11Extension(
        "strgraphcpp",
        [
            "src/csrc/Binding.cpp",
            "src/csrc/Graph.cpp",
            "src/csrc/Node.cpp",
            "src/csrc/Scheduler.cpp",
            "src/csrc/stringOp/ConcateOp.cpp",
            "src/csrc/stringOp/InputOp.cpp",
            "src/csrc/stringOp/IOReadOp.cpp",
            "src/csrc/stringOp/IOWriteOp.cpp",
            "src/csrc/stringOp/pyStringOp.cpp",
            "src/csrc/stringOp/stringOpFactory.cpp",
        ],
        include_dirs=[include_dir],
        cxx_std=17,
        # 如果需要调试信息，可以取消下面这一行的注释
        extra_compile_args=['-g', '-O0', '-std=c++17'],
    ),
]

# 设置包目录，指向 'src/py'
setup(
    name='strgraphcpp',
    version='1.0.0',
    author='Andy Ho',
    author_email='He_minghao@outlook.com',
    description='High-performance string operation computation graph system',
    long_description=open('README.md').read() if os.path.exists('README.md') else 'README',
    long_description_content_type='text/markdown',
    packages=find_packages(),
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    install_requires=[
        'pybind11>=2.5.0',
    ],
    include_package_data=True,
    zip_safe=False,
)
