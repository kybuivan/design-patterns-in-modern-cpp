function(make_executable_folder subfolders)
    foreach(_dir IN ITEMS ${subfolders})
        file(GLOB _files "${_dir}/*.cpp")
        message(STATUS "Pattern `${_dir}':")

        foreach(_file IN ITEMS ${_files})

            get_filename_component(_file_name ${_file} NAME )

            set(_project_name "${_file_name}")
            message(STATUS "  ${_dir}/${_file_name} is going to be built")

            add_executable(${_project_name} "${_dir}/${_file_name}")
            target_compile_features(${_project_name} PRIVATE cxx_std_17)
            add_test(NAME ${_project_name} COMMAND ${_project_name})
        endforeach()
    endforeach()
endfunction(make_executable_folder)
