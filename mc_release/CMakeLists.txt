cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(NAMESPACE fp_pr)
set(COMPONENT release)
project(${NAMESPACE}_${COMPONENT}
    VERSION 1.0.0
    LANGUAGES CXX
)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

add_executable(${NAMESPACE}::${COMPONENT} ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

find_package(fp_core 1.0.0 REQUIRED)
target_link_libraries(${PROJECT_NAME} fp_pr::core)
