
set(target_name  ifxOptTest)

set(source_files
    ifxOptTestMain.cpp)

add_executable(${target_name} ${source_files})

target_link_libraries(${target_name}
                      ifxOpt)
