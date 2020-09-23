cmake_minimum_required(VERSION 2.6)

project (phonebookserver CXX)

# Add cmake scripts
include(tools/cmake/tests.cmake)

set(PHONEBOOK_HEADERS RestServer.h Contact.h)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PHONEBOOK_CODEGEN_DIR "${PROJECT_BINARY_DIR}/codegen")

PREPEND(PHONEBOOK_HEADERS_PATHS ${PROJECT_SOURCE_DIR} ${PHONEBOOK_HEADERS})

CODEGEN_FILES(
    PHONEBOOK_CODEGEN_SOURCES
        ${PHONEBOOK_CODEGEN_DIR}
        ${PHONEBOOK_HEADERS}
)

add_custom_command(OUTPUT ${PHONEBOOK_CODEGEN_SOURCES}
    COMMAND ${NGREST_BIN_PATH}ngrestcg -i "${PROJECT_SOURCE_DIR}" -o ${PHONEBOOK_CODEGEN_DIR} -t service ${PHONEBOOK_HEADERS}
    DEPENDS ${PHONEBOOK_HEADERS_PATHS}
)

file(GLOB_RECURSE PHONEBOOK_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

list(APPEND PHONEBOOK_SOURCES ${PHONEBOOK_CODEGEN_SOURCES})

include_directories(src $ENV{NGREST_EXT_INCLUDES})

add_library(
    ${PROJECT_NAME}
        MODULE
        ${PHONEBOOK_SOURCES}
        src/Contact.h
        src/include/AuthBundle.h
        src/include/AuthToken.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
set_target_properties(
    ${PROJECT_NAME}
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY
        "${PROJECT_SERVICES_DIR}"
)

target_link_libraries(
    ${PROJECT_NAME}
        ngrestutils
        ngrestcommon
        ngrestjson
        ngrestengine
        $ENV{NGREST_EXT_LIBS}
)

# To disable tests, comment these two lines
enable_testing()
add_subdirectory(tests)

## Unit tests target
add_custom_target(RunAllTests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    COMMENT "Run all tests"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/back-end/tests
)