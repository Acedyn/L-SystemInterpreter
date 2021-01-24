# Define source files
file(GLOB SOURCES
    "*.cpp")

# Define header files
file(GLOB HEADERS
    "*.h")

# Define an executable for test
add_executable(l-SystemBaseTest
    ${SOURCES}
    ${HEADERS})

target_link_libraries(l-SystemBaseTest
    l-SystemBase)

# Define the output directory
if(DEFINED LSYSTEM_OUTPUT_DIR)
    set_target_properties(l-SystemBaseTest
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${LSYSTEM_OUTPUT_DIR}/l-SystemBaseTest")
endif()
