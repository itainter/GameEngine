file(GLOB SRC_LOG
    "*.cpp"
    "*.h"
)

add_library(
    Log
    ${SRC_LOG}
)

set_target_properties(
    Log
    PROPERTIES
    FOLDER ${FOLDER_ENGINE}
)