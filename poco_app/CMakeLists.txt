cmake_minimum_required (VERSION 3.0)
set (PWS pocowebserver)

project (${PWS} VERSION 0.0.1)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_CXX_STANDARD 17)

set (ENTRYPOINT_PWS
	"${CMAKE_CURRENT_LIST_DIR}/src/main.cpp"
) 

set (HEADERS_PWS
    "${CMAKE_CURRENT_LIST_DIR}/include/server/serverapplication.hpp"
    "${CMAKE_CURRENT_LIST_DIR}/include/server/base.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/server/handlers/htmlhandler.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/server/handlers/csshandler.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/server/handlers/jshandler.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/server/handlers/imghandler.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/server/handlers/errorhtmlhandler.hpp"
    "${CMAKE_CURRENT_LIST_DIR}/include/server/api/api.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/server/api/getUsers.hpp"    
)

set(SOURCES_PWS
    "${CMAKE_CURRENT_LIST_DIR}/src/server/serverapplication.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/server/base.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/src/server/handlers/htmlhandler.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/src/server/handlers/csshandler.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/src/server/handlers/jshandler.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/src/server/handlers/imghandler.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/src/server/handlers/errorhtmlhandler.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/server/api/api.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/src/server/api/getUsers.cpp"
)

set(RESOURCES_PWS
    #
)

###

configure_file(
    "${CMAKE_CURRENT_LIST_DIR}/include/pws_config.h.in" 
    "${CMAKE_CURRENT_LIST_DIR}/include/pws_config.h"
)

set (CONFIGURATION_PWS 
    "${CMAKE_CURRENT_LIST_DIR}/include/pws_config.h"
)

###

add_subdirectory(
    "${CMAKE_CURRENT_LIST_DIR}/libs/poco"
)

add_subdirectory(
    "${CMAKE_CURRENT_LIST_DIR}/libs/toml"
)

add_subdirectory(
    "${CMAKE_CURRENT_LIST_DIR}/libs/termcolor"
)

###

add_executable(
    ${PWS} 
        ${ENTRYPOINT_PWS} 
        ${CONFIGURATION_PWS}
        ${HEADERS_PWS} 
        ${SOURCES_PWS} 
        ${RESOURCES_PWS}
)

    target_include_directories(
        ${PWS}
            PRIVATE
                "${CMAKE_CURRENT_LIST_DIR}/include"
    )


    target_link_libraries(
        ${PWS} 
            Poco::Foundation 
            Poco::Net 
            Poco::Util
            # Poco::Data
            # Poco::DataPostgreSQL
    ) 

    target_link_libraries(
        ${PWS}
            toml11::toml11
            termcolor::termcolor
	)