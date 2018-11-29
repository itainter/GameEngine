file(GLOB_RECURSE SRC_DEFAULT_APP
    "*.cpp"
    "*.h"
)

add_executable(
    DefaultApp
    ${SRC_DEFAULT_APP}
)

target_link_libraries(
    DefaultApp
    Common
    Graphics
    Log
)

set_target_properties(
    DefaultApp
    PROPERTIES
    FOLDER ${FOLDER_APP}
)