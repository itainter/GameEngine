file(GLOB SRC_WINDOWS_APP
    "*.cpp"
    "*.h"
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/Windows)

file(GLOB RUNTIME_FILES
    ${PROJECT_SOURCE_DIR}/Thirdparts/*/Bin/*.dll)
file(COPY ${RUNTIME_FILES} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Debug)
file(COPY ${PROJECT_SOURCE_DIR}/Asset DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Debug)

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
    RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
)

