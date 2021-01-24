# Define source files
file(GLOB SOURCES
    "private/l-SystemDraw/*.cpp")

# Define header files
file(GLOB HEADERS
    "public/l-SystemDraw/*.h")

# Create library for L-SystemBase
add_library(l-SystemDraw
    ${SOURCES}
    ${HEADERS})

# Add include directories as public so the user can use it
# Private directory is included a private because the user will not use it
target_include_directories(l-SystemDraw
    PUBLIC public
    PRIVATE private)

target_link_libraries(l-SystemDraw
    Imath::Imath
    l-SystemBase)

# Define the output directory
if(DEFINED LSYSTEM_OUTPUT_DIR)
    set_target_properties(l-SystemDraw
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${LSYSTEM_OUTPUT_DIR}/l-SystemDraw")
endif()
