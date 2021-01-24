# Define source files
file(GLOB SOURCES
    "private/l-SystemBase/*.cpp")

# Define header files
file(GLOB HEADERS
    "public/l-SystemBase/*.h")

# Create library for L-SystemBase
add_library(l-SystemBase
    ${SOURCES}
    ${HEADERS})

# Add include directories as public so the user can use it
# Private directory is included a private because the user will not use it
target_include_directories(l-SystemBase
    PUBLIC public
    PRIVATE private)

# Define the output directory
if(DEFINED LSYSTEM_OUTPUT_DIR)
    set_target_properties(l-SystemBase
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${LSYSTEM_OUTPUT_DIR}/l-SystemBase")
endif()
