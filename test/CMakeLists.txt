cmake_minimum_required(VERSION 3.12)
project(Examples LANGUAGES CXX)

find_package(Protobuf CONFIG REQUIRED)

# Build proto lib
add_library(myproto
  test.proto
)
target_link_libraries(myproto
  PUBLIC
    protobuf::libprotobuf
)
protobuf_generate(
  TARGET myproto
  LANGUAGE cpp
)
target_include_directories(myproto
  PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Build test
add_executable(test
  test.cpp
)
target_link_libraries(test
  myproto
)
