cmake_minimum_required(VERSION 3.5)

project(design_patterns)

# Global CMake variables are set here
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PATTERNS
    #abstract-factory
    adapter
    bridge
    builder
    command
    composite
    decorator
    facade
    factory
    flyweight
    iterator
    mediator
    memento
    observer
    prototype
    proxy
    singleton
    state
    strategy
    template-method
    visitor
)

foreach(_dir IN ITEMS ${PATTERNS})
    file(GLOB _files "${_dir}/*.cpp")
    message(STATUS "Pattern `${_dir}':")

    foreach(_file IN ITEMS ${_files})

        get_filename_component(_file_name
                                ${_file} NAME
        )

        set(_project_name "${_file_name}")
        message(STATUS "  ${_dir}/${_file_name} is going to be built")

        add_executable(${_project_name} "${_dir}/${_file_name}")
        target_compile_features(${_project_name} PRIVATE cxx_std_17)  # Add this line
    endforeach()

endforeach()
