cmake_minimum_required(VERSION 3.10)
project(GameLib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
file(GLOB_RECURSE HEADER_FILES "include/*.h" "include/*.hpp")
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.cc")

add_executable(exec ${SOURCE_FILES} ${HEADER_FILES})
if(APPLE)
	target_link_libraries(exec PRIVATE iconv)
endif()

target_compile_options(exec PRIVATE -Wno-deprecated-declarations)
