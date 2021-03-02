# Define source files
file(GLOB SOURCES
    "private/l-SystemDraw/*.cpp")

# Define header files
file(GLOB HEADERS
    "public/l-SystemDraw/*.h")

# If USD is not found
if(NOT ${pxr_FOUND})
    # Remove all the files that uses USD
    list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/private/l-SystemDraw/l-SystemOutputUSD.cpp")
    list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/public/l-SystemDraw/l-SystemOutputUSD.h")
    message(${SOURCES})
endif()

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
    Imath::Imath_static
    l-SystemBase)

# Link the usd targets only of the usd library has been found
if(${pxr_FOUND})
    target_link_libraries(l-SystemDraw
        usd
        usdGeom
        tf
        sdf
        vt)
endif()

# Define the output directory
if(DEFINED LSYSTEM_OUTPUT_DIR)
    set_target_properties(l-SystemDraw
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${LSYSTEM_OUTPUT_DIR}/l-SystemDraw")
endif()
