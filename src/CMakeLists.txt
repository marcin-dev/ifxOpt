
set(target_name  ifxOpt)

set(source_files
    ifxOpt.cpp
    ifxOptEntryInt.cpp
    )

add_library(${target_name} ${source_files})

target_include_directories(${target_name} PUBLIC
                           ../include
                           )