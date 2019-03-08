file(GLOB SRC_DEFAULT_APP
    "*.cpp"
    "*.h"
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/Default)

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
    RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
)