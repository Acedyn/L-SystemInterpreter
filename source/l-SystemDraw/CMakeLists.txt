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

if(WIN32)
    set_target_properties(l-SystemDraw
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/binaries/l-SystemDraw/vs2019")
endif(WIN32)

if(MINGW)
    set_target_properties(l-SystemDraw
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/binaries/l-SystemDraw/mingw")
endif(MINGW)

if(UNIX)
    set_target_properties(l-SystemDraw
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/binaries/l-SystemDraw/unix")
endif(UNIX)

