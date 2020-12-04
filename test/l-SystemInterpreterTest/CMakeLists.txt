# Define source files
file(GLOB SOURCES
    "*.cpp")

# Define header files
file(GLOB HEADERS
    "*.h")

# Define an executable for test
add_executable(l-SystemInterpreterTest
    ${SOURCES}
    ${HEADERS})

target_link_libraries(l-SystemInterpreterTest
    l-SystemInterpreter)

if(WIN32)
    set_target_properties(l-SystemInterpreterTest
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/binaries/l-SystemInterpreterTest/vs2019")
endif(WIN32)

if(MINGW)
    set_target_properties(l-SystemInterpreterTest
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/binaries/l-SystemInterpreterTest/mingw")
endif(MINGW)

