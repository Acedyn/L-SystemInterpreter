# Define source files
file(GLOB SOURCES
    "*.cpp")

# Define header files
file(GLOB HEADERS
    "*.h")

# Define an executable for test
add_executable(l-SystemDrawTest
    ${SOURCES}
    ${HEADERS})

target_link_libraries(l-SystemDrawTest
    l-SystemDraw)

# Deifine the output directory
if(DEFINED LSYSTEM_OUTPUT_DIR)
    set_target_properties(l-SystemDrawTest
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${LSYSTEM_OUTPUT_DIR}/l-SystemDrawTest")
endif()
