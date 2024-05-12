cmake_minimum_required(VERSION 3.5)

# 设置工程名称
project(NesEmulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Werror)

# 添加可执行文件
add_executable(cpu_test test/cpu_test.cc src/cpu.cc)
target_include_directories(cpu_test PRIVATE
  src
  3rdparty/raylib-5.0_linux_amd64/include)

target_link_directories(cpu_test PRIVATE
  3rdparty/raylib-5.0_linux_amd64/lib)
target_link_libraries(cpu_test raylib)

# 添加可选的库文件搜索路径
# link_directories(lib)

# 添加链接的库文件
# target_link_libraries(MyExecutable MyLibrary)
