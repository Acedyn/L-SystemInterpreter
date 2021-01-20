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

if(WIN32)
    set_target_properties(l-SystemBaseTest
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/binaries/l-SystemBaseTest/vs2019")
endif(WIN32)

if(MINGW)
    set_target_properties(l-SystemBaseTest
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/binaries/l-SystemBaseTest/mingw")
endif(MINGW)

if(UNIX)
    set_target_properties(l-SystemBaseTest
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/binaries/l-SystemBaseTest/unix")
endif(UNIX)

