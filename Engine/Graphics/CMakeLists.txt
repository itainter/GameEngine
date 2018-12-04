file(GLOB SRC_DEVICE
    "Device/*.cpp"
    "Device/*.h"
)

file(GLOB SRC_D3D11
    "Device/D3D11/*.cpp"
    "Device/D3D11/*.h"
)

add_library(
    Graphics
    ${SRC_DEVICE}
    ${SRC_D3D11}
)

source_group(Device FILES ${SRC_DEVICE})
source_group(Device\\D3D11 FILES ${SRC_D3D11})

set_target_properties(
    Graphics
    PROPERTIES
    FOLDER ${FOLDER_ENGINE}
)