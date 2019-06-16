
set(target_name  ifxOptTest)

set(source_files
    ifxOptTestMain.cpp
    )
    
add_executable(${target_name} ${source_files})

#target_include_directories(${target_name} PUBLIC
#                           ../include
#                           )

target_link_libraries(${target_name}
                      ifxOpt
                      )
