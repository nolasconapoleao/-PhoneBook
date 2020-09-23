set(EXECUTABLE_NAME unit_Controller)

add_executable(
    ${EXECUTABLE_NAME}
        # Sources
        ut_Controller.cpp
)

target_sources(
    ${EXECUTABLE_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/back-end/src/authentication/AccountDb.cpp
        ${CMAKE_SOURCE_DIR}/back-end/src/authentication/AccountManager.cpp
        ${CMAKE_SOURCE_DIR}/back-end/src/authentication/Cypher.cpp
        ${CMAKE_SOURCE_DIR}/back-end/src/contact/ContactDb.cpp
        ${CMAKE_SOURCE_DIR}/back-end/src/Controller.cpp
)

target_link_libraries(
    ${EXECUTABLE_NAME}
        ngrestutils
        ngrestcommon
        ngrestjson
        ngrestengine
        $ENV{NGREST_EXT_LIBS}
)

create_test(${EXECUTABLE_NAME})
