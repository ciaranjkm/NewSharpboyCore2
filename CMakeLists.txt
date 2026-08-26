cmake_minimum_required(VERSION 4.4.2)
project(NewSharpboyCore)

add_library(NewSharpboyCore STATIC)

target_sources(NewSharpboyCore PRIVATE src/core.cpp)
target_include_directories(NewSharpboyCore PUBLIC "include")