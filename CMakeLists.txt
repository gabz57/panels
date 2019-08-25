cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(panels)

include_directories(${PROJECT_SOURCE_DIR}/libs/matrix/lib)
include_directories(${PROJECT_SOURCE_DIR}/libs/matrix/include)

include_directories(${PROJECT_SOURCE_DIR}/libs/matrix-ui/src)
include_directories(${PROJECT_SOURCE_DIR}/libs/matrix-ui/include/matrix-ui)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE RGB_SRC_FILES ${PROJECT_SOURCE_DIR}/libs/matrix/lib/*.cc)
file(GLOB_RECURSE RGB_SRC_C_FILES ${PROJECT_SOURCE_DIR}/libs/matrix/lib/*.c)
file(GLOB_RECURSE RGB_HEADER_FILES ${PROJECT_SOURCE_DIR}/libs/matrix/include/*.h)

file(GLOB_RECURSE UI_SRC_FILES ${PROJECT_SOURCE_DIR}/libs/matrix-ui/src/*.cpp)
file(GLOB_RECURSE UI_HEADER_FILES ${PROJECT_SOURCE_DIR}/libs/matrix-ui/include/matrix-ui/*.h)
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/include/*.h)

add_executable(panels src/panels.cpp ${HW_HEADER_FILE}  /
        ${RGB_SRC_FILES} ${RGB_SRC_C_FILES} ${RGB_HEADER_FILES}  /
        ${UI_SRC_FILES} ${UI_HEADER_FILES} /
        ${SRC_FILES} ${HEADER_FILES})
#link_directories(${CMAKE_BINARY_DIR}/libs/matrix/lib)
target_link_libraries(panels -lpthread)
#target_link_libraries(panels -lpthread)