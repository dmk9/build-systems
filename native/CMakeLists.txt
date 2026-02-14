cmake_minimum_required(VERSION 3.15)
project(BuildSystemsNative VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Library source files
set(SOURCES
    src/calculator.cpp
)

# Create library
add_library(${PROJECT_NAME} STATIC ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Executable for testing
add_executable(demo src/main.cpp)
target_link_libraries(demo ${PROJECT_NAME})

# Installation rules
install(TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY include/
    DESTINATION include
)

# Enable testing
enable_testing()
add_test(NAME DemoTest COMMAND demo)
