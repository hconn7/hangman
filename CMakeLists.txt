cmake_minimum_required(VERSION 3.20)
project(MyProject LANGUAGES CXX)

# Enforce C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export compile_commands.json so clangd understands multi-file includes
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define your executable and list ALL your .cpp source files here
add_executable(my_app main.cpp
)
