cmake_minimum_required(VERSION 3.2)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
set(CMAKE_CXX_STANDARD 17)

if (POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()

project(nanowars)
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)

add_definitions( "-DHAS_BOOST" )

find_package(SFGUI REQUIRED)
find_package(SFML 2.4.2 REQUIRED COMPONENTS system audio graphics window)
find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(Rapidjson REQUIRED)
find_package(Box2D REQUIRED)

link_directories(${Boost_LIBRARY_DIRS})

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

if(BUILD_TESTS)
    include_directories(${CATCH2_INCLUDE_DIR})
    file(GLOB_RECURSE SOURCE_TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)
    add_executable(nanowars_tests ${SOURCE_TEST_FILES} ${SOURCE_FILES})
    target_link_libraries(nanowars_tests ${SFML_LIBRARIES} ${SFGUI_LIBRARY} ${BOX2D_LIBRARY} ${Boost_LIBRARIES})
    target_compile_definitions(nanowars_tests PRIVATE TEST_BUILD)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${SFML_INCLUDE_DIR})
include_directories(${SFGUI_INCLUDE_DIR})
include_directories(${BOX2D_INCLUDE_DIR})
include_directories(${RAPIDJSON_INCLUDEDIR})

add_executable(nanowars ${SOURCE_FILES})

target_link_libraries(nanowars ${SFML_LIBRARIES} ${SFGUI_LIBRARY} ${BOX2D_LIBRARY} ${Boost_LIBRARIES})
