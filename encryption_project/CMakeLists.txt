cmake_minimum_required(VERSION 3.11)
project(cyphers)

find_package(pybind11 REQUIRED)
set(CMAKE_CXX_STANDARD 11)

pybind11_add_module(cyphers cyphers.cpp)

# /home/ghukii/anaconda3/lib/python3.11/site-packages/pybind11
