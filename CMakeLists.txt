cmake_minimum_required(VERSION 3.28)
project(Tut1 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Automatically adds all cpp files contained in the src directory
file(GLOB_RECURSE source_files
    "src/*.cpp"
)
set(SOURCES ${source_files})
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
        "inc/")

# Link libraries to target
target_link_libraries(${PROJECT_NAME} SFML::System SFML::Window SFML::Graphics SFML::Audio SFML::Network)

# add_custom_command(TARGET ${PROJECT_NAME}
#     COMMENT "Copying resources to build directory"
#     PRE_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
# )