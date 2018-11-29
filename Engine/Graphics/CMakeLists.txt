file(GLOB_RECURSE SRC_DEVICE
    "Device/*.cpp"
    "Device/*.h"
)

add_library(
    Graphics
    ${SRC_DEVICE}
)

source_group("Device" FILES ${SRC_DEVICE})

set_target_properties(
    Graphics
    PROPERTIES
    FOLDER ${FOLDER_ENGINE}
)