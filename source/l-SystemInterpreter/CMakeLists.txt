# Define source files
file(GLOB SOURCES
    "private/l-SystemInterpreter/*.cpp")

# Define header files
file(GLOB HEADERS
    "public/l-SystemInterpreter/*.h")

# Create library for L-SystemInterpreter
add_library(l-SystemInterpreter
    ${SOURCES}
    ${HEADERS})

# Add include directories as public so the user can use it
# Private directory is included a private because the user will not use it
target_include_directories(l-SystemInterpreter 
    PUBLIC public
    PRIVATE private)

if(WIN32)
    set_target_properties(l-SystemInterpreter
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/binaries/l-SystemInterpreter/vs2019")
endif(WIN32)

if(MINGW)
    set_target_properties(l-SystemInterpreter
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/binaries/l-SystemInterpreter/mingw")
endif(MINGW)

