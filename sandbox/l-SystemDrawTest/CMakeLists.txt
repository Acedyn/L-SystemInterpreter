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

if(WIN32)
    set_target_properties(l-SystemDrawTest
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/binaries/l-SystemDrawTest/vs2019")
endif(WIN32)

if(MINGW)
    set_target_properties(l-SystemDrawTest
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/binaries/l-SystemDrawTest/mingw")
endif(MINGW)

if(UNIX)
    set_target_properties(l-SystemDrawTest
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/binaries/l-SystemDrawTest/unix")
endif(UNIX)

