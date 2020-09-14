set(EXECUTABLE_NAME unit_Phonebook)

add_executable(
    ${EXECUTABLE_NAME}
        # Sources
        ut_Phonebook.cpp
)

target_sources(
    ${EXECUTABLE_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/restserver/src/ContactList.cpp
        ${CMAKE_SOURCE_DIR}/restserver/src/Phonebook.cpp
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
