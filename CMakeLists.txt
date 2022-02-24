cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_TOOLCHAIN_FILE /opt/vcpkg/scripts/buildsystems/vcpkg.cmake)

enable_language(CXX)
project(TGOL)

find_package(SFML 2 REQUIRED graphics)

include_directories(${SFML_INCLUDE_DIR})
add_executable(TGOL src/main.cpp)
target_link_libraries(TGOL PRIVATE sfml-graphics)