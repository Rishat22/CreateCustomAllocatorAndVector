cmake_minimum_required(VERSION 3.5)

project(custom_allocator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(project_sources
    main.cpp
    custom_allocator.hpp
    vector_iterator.hpp
    vector.hpp
    )

add_executable(custom_allocator ${project_sources} )
