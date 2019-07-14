
set(target_name  ifxOpt)

set(source_files
    ifxOpt.cpp
    ifxArgEntryBase.cpp
    ifxOptEntryBase.cpp
    internal/ifxArgEntry.cpp
    internal/ifxInternalUtils.cpp
    internal/ifxOptEntry_int.cpp
    internal/ifxOptEntry_string.cpp
    )

add_library(${target_name} ${source_files})

target_include_directories(${target_name} PUBLIC
                           ../include
                           )

target_compile_definitions(${target_name} PRIVATE "-DDEBUG_LOG_ENABLED")
