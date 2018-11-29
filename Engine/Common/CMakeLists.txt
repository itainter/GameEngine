file(GLOB_RECURSE SRC_COMMON
    "*.cpp"
    "*.h"
)

file(GLOB_RECURSE SRC_INTERFACE
    "../Interface/*.h"
)

file(GLOB_RECURSE SRC_UTIL
    "../Util/*.cpp"
    "../Util/*.h"
)

source_group("Interface" FILES ${SRC_INTERFACE})
source_group("Uitl" FILES ${SRC_UTIL})

add_library(
    Common
    ${SRC_COMMON}
    ${SRC_UTIL}
    ${SRC_INTERFACE}
)

set_target_properties(
    Common
    PROPERTIES
    FOLDER ${FOLDER_ENGINE}
)