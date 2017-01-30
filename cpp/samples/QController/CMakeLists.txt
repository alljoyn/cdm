cmake_minimum_required(VERSION 3.5)
project(QController)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug)
ENDIF(NOT CMAKE_BUILD_TYPE)

IF(NOT OS)
    SET(OS darwin)
ENDIF(NOT OS)

IF(NOT CPU)
    SET(CPU x86_64)
ENDIF(NOT CPU)

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
    qcTypes.h
    qcUtils.h
    qcUtils.cpp
    InspectorWidget.cpp
    InspectorWidget.h
    )

file(GLOB INTERFACE_SOURCE_FILES
    interfaces/*.cpp
    interfaces/*.h
    interfaces/WarpCore/*.cc
    interfaces/WarpCore/*.h
)

IF(NOT CDM_DIST)
    string(TOLOWER ${CMAKE_BUILD_TYPE} VARIANT)
    set(CDM_DIST "${PROJECT_SOURCE_DIR}/../../../build/${OS}/${CPU}/${VARIANT}/dist")
ENDIF(NOT CDM_DIST)

include_directories(SYSTEM
    $ENV{ALLJOYN_DISTDIR}/cpp/inc
    ${CDM_DIST}/cdm/framework/inc
    ${CDM_DIST}/cdm/interfaces/inc
)

link_directories(
    $ENV{ALLJOYN_DISTDIR}/cpp/lib
    ${CDM_DIST}/cdm/lib
)


IF (APPLE)
    add_definitions(
        -DQCC_OS_GROUP_POSIX
        -DQCC_OS_DARWIN
        -DQCC_CPU_X86
        -DALLJOYN_BUNDLED_ROUTER
    )
    add_executable(QController ${SOURCE_FILES} ${INTERFACE_SOURCE_FILES})
    target_link_libraries(QController Qt5::Widgets
            ${CDM_DIST}/cdm/lib/liballjoyn_cdm_common.a
            ${CDM_DIST}/cdm/lib/liballjoyn_cdm_controller.a
            ${CDM_DIST}/cdm/lib/liballjoyn_cdm_interfaces.a
            ${CDM_DIST}/cdm/lib/liballjoyn_cdm_util.a
            alljoyn ajrouter)
ELSEIF(WIN32)
    add_definitions(
            -DQCC_OS_GROUP_WINDOWS
            -DQCC_CPU_X64
            -DALLJOYN_BUNDLED_ROUTER
    )
    add_executable(QController ${SOURCE_FILES} ${INTERFACE_SOURCE_FILES})
    target_link_libraries(QController Qt5::Widgets
            ${CDM_DIST}/cdm/lib/liballjoyn_cdm_common.lib
            ${CDM_DIST}/cdm/lib/liballjoyn_cdm_controller.lib
            ${CDM_DIST}/cdm/lib/liballjoyn_cdm_interfaces.lib
            ${CDM_DIST}/cdm/lib/liballjoyn_cdm_util.lib
            alljoyn ajrouter)

ENDIF()