file(GLOB SRC_EVENT_TEST
    "*.cpp"
)

add_executable(
    EventTest
    ${SRC_EVENT_TEST}
)

target_link_libraries(
    EventTest
    Common
)

set_target_properties(
    EventTest
    PROPERTIES
    FOLDER ${FOLDER_TEST}
)