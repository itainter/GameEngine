file(GLOB_RECURSE SRC_WINDOWS_APP
    "*.cpp"
    "*.h"
)

add_executable(
    WindowsApp
    ${SRC_WINDOWS_APP}
)

target_link_libraries(
    WindowsApp
    Common
    Graphics
    Log
)

set_target_properties(
    WindowsApp
    PROPERTIES
    FOLDER ${FOLDER_APP}
)