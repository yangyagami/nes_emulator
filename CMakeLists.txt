cmake_minimum_required(VERSION 3.5)

# 设置工程名称
project(NesEmulator)

add_compile_options(-Wall -Werror)

# 添加可执行文件
add_executable(test test/test.cc src/cpu.cc)

# 添加可选的库文件搜索路径
# link_directories(lib)

# 添加链接的库文件
# target_link_libraries(MyExecutable MyLibrary)
