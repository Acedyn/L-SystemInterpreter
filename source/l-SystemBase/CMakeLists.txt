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

if(WIN32)
    set_target_properties(l-SystemBase
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/binaries/l-SystemBase/vs2019")
endif(WIN32)

if(MINGW)
    set_target_properties(l-SystemBase
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/binaries/l-SystemBase/mingw")
endif(MINGW)

if(UNIX)
    set_target_properties(l-SystemBase
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/binaries/l-SystemBase/unix")
endif(UNIX)

