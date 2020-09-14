cmake_minimum_required(VERSION 2.6)

project (phonebookserver CXX)

# Add cmake scripts
include(tools/cmake/tests.cmake)

set(PHONEBOOKSERVER_HEADERS RestServer.h Contact.h)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PHONEBOOKSERVER_CODEGEN_DIR "${PROJECT_BINARY_DIR}/codegen")

PREPEND(PHONEBOOKSERVER_HEADERS_PATHS ${PROJECT_SOURCE_DIR} ${PHONEBOOKSERVER_HEADERS})

CODEGEN_FILES(PHONEBOOKSERVER_CODEGEN_SOURCES ${PHONEBOOKSERVER_CODEGEN_DIR} ${PHONEBOOKSERVER_HEADERS})

add_custom_command(OUTPUT ${PHONEBOOKSERVER_CODEGEN_SOURCES}
    COMMAND ${NGREST_BIN_PATH}ngrestcg -i "${PROJECT_SOURCE_DIR}" -o ${PHONEBOOKSERVER_CODEGEN_DIR} -t service ${PHONEBOOKSERVER_HEADERS}
    DEPENDS ${PHONEBOOKSERVER_HEADERS_PATHS}
)

file(GLOB PHONEBOOKSERVER_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

list(APPEND PHONEBOOKSERVER_SOURCES ${PHONEBOOKSERVER_CODEGEN_SOURCES})

include_directories(${PROJECT_SOURCE_DIR} $ENV{NGREST_EXT_INCLUDES})

add_library(phonebookserver MODULE ${PHONEBOOKSERVER_SOURCES} src/Contact.h)

set_target_properties(phonebookserver PROPERTIES PREFIX "")
set_target_properties(phonebookserver PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SERVICES_DIR}"
)

target_link_libraries(phonebookserver ngrestutils ngrestcommon ngrestjson ngrestengine $ENV{NGREST_EXT_LIBS})

# To disable tests, comment these two lines
enable_testing()
add_subdirectory(tests)

## Unit tests target
add_custom_target(RunAllTests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    COMMENT "Run all tests"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/restserver/tests
)