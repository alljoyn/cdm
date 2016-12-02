cmake_minimum_required(VERSION 3.5)
project(QController)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


find_package(Qt5Widgets)

set(SOURCE_FILES
    commoncontrollerdevice.cpp
    commoncontrollerimpl.h
    commoncontrollerinterface.cpp
    commoncontrollermodel.cpp
    commoncontrollermodel.h
    commoncontrollerpath.cpp
    commoncontrollerroot.cpp
    LogModel.cpp
    LogModel.h
    main.cpp
    qcontroller.cpp
    qcontroller.h
    InspectorWidget.cpp
    InspectorWidget.h
    )

file(GLOB INTERFACE_SOURCE_FILES
    interfaces/*.cpp
    interfaces/*.h
)

set(ALLJOYN_DIST "${PROJECT_SOURCE_DIR}/../../../build/darwin/x86_64/debug/dist")

include_directories(SYSTEM
    ${ALLJOYN_DIST}/cpp/inc
    ${ALLJOYN_DIST}/cdm/inc
)

link_directories(
    ${ALLJOYN_DIST}/cpp/lib
    ${ALLJOYN_DIST}/cdm/lib
)

add_definitions(
    -DQCC_OS_GROUP_POSIX
    -DQCC_OS_DARWIN
    -DQCC_CPU_X86
    -DALLJOYN_BUNDLED_ROUTER
)

add_executable(QController ${SOURCE_FILES} ${INTERFACE_SOURCE_FILES})
target_link_libraries(QController Qt5::Widgets ${ALLJOYN_DIST}/cdm/lib/liballjoyn_cdm.a alljoyn ajrouter)
